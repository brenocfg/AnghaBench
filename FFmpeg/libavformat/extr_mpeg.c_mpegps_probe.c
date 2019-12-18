#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int buf_size; int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AUDIO_ID ; 
 int AVPROBE_SCORE_EXTENSION ; 
 int PACK_START_CODE ; 
 int PRIVATE_STREAM_1 ; 
 int SYSTEM_HEADER_START_CODE ; 
 int VIDEO_ID ; 
 int check_pack_header (int*) ; 
 scalar_t__ check_pes (int*,int*) ; 

__attribute__((used)) static int mpegps_probe(const AVProbeData *p)
{
    uint32_t code = -1;
    int i;
    int sys = 0, pspack = 0, priv1 = 0, vid = 0;
    int audio = 0, invalid = 0, score = 0;
    int endpes = 0;

    for (i = 0; i < p->buf_size; i++) {
        code = (code << 8) + p->buf[i];
        if ((code & 0xffffff00) == 0x100) {
            int len  = p->buf[i + 1] << 8 | p->buf[i + 2];
            int pes  = endpes <= i && check_pes(p->buf + i, p->buf + p->buf_size);
            int pack = check_pack_header(p->buf + i);

            if (code == SYSTEM_HEADER_START_CODE)
                sys++;
            else if (code == PACK_START_CODE && pack)
                pspack++;
            else if ((code & 0xf0) == VIDEO_ID && pes) {
                endpes = i + len;
                vid++;
            }
            // skip pes payload to avoid start code emulation for private
            // and audio streams
            else if ((code & 0xe0) == AUDIO_ID &&  pes) {audio++; i+=len;}
            else if (code == PRIVATE_STREAM_1  &&  pes) {priv1++; i+=len;}
            else if (code == 0x1fd             &&  pes) vid++; //VC1

            else if ((code & 0xf0) == VIDEO_ID && !pes) invalid++;
            else if ((code & 0xe0) == AUDIO_ID && !pes) invalid++;
            else if (code == PRIVATE_STREAM_1  && !pes) invalid++;
        }
    }

    if (vid + audio > invalid + 1) /* invalid VDR files nd short PES streams */
        score = AVPROBE_SCORE_EXTENSION / 2;

//     av_log(NULL, AV_LOG_ERROR, "vid:%d aud:%d sys:%d pspack:%d invalid:%d size:%d \n",
//            vid, audio, sys, pspack, invalid, p->buf_size);

    if (sys > invalid && sys * 9 <= pspack * 10)
        return (audio > 12 || vid > 3 || pspack > 2) ? AVPROBE_SCORE_EXTENSION + 2
                                                     : AVPROBE_SCORE_EXTENSION / 2 + 1; // 1 more than mp3
    if (pspack > invalid && (priv1 + vid + audio) * 10 >= pspack * 9)
        return pspack > 2 ? AVPROBE_SCORE_EXTENSION + 2
                          : AVPROBE_SCORE_EXTENSION / 2; // 1 more than .mpg
    if ((!!vid ^ !!audio) && (audio > 4 || vid > 1) && !sys &&
        !pspack && p->buf_size > 2048 && vid + audio > invalid) /* PES stream */
        return (audio > 12 || vid > 6 + 2 * invalid) ? AVPROBE_SCORE_EXTENSION + 2
                                                     : AVPROBE_SCORE_EXTENSION / 2;

    // 02-Penguin.flac has sys:0 priv1:0 pspack:0 vid:0 audio:1
    // mp3_misidentified_2.mp3 has sys:0 priv1:0 pspack:0 vid:0 audio:6
    // Have\ Yourself\ a\ Merry\ Little\ Christmas.mp3 0 0 0 5 0 1 len:21618
    return score;
}