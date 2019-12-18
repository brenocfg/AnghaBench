#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* av_err2str (int) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int av_packet_add_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * av_packet_side_data_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int setup_side_data_entry(AVPacket* avpkt)
{
    const uint8_t *data_name = NULL;
    int ret = 0, bytes;
    uint8_t *extra_data = NULL;


    /* get side_data_name string */
    data_name = av_packet_side_data_name(AV_PKT_DATA_NEW_EXTRADATA);

    /* Allocate a memory bloc */
    bytes = strlen(data_name);

    if(!(extra_data = av_malloc(bytes))){
        ret = AVERROR(ENOMEM);
        fprintf(stderr, "Error occurred: %s\n", av_err2str(ret));
        exit(1);
    }
    /* copy side_data_name to extra_data array */
    memcpy(extra_data, data_name, bytes);

    /* create side data for AVPacket */
    ret = av_packet_add_side_data(avpkt, AV_PKT_DATA_NEW_EXTRADATA,
                                        extra_data, bytes);
    if(ret < 0){
        fprintf(stderr,
                "Error occurred in av_packet_add_side_data: %s\n",
                av_err2str(ret));
    }

    return ret;
}