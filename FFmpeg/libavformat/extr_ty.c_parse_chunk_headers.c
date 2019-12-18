#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int rec_type; int subrec_type; int* ex; int rec_size; int /*<<< orphan*/  ty_pts; } ;
typedef  TYPE_1__ TyRecHdr ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB64 (int const*) ; 
 TYPE_1__* av_calloc (int,int) ; 

__attribute__((used)) static TyRecHdr *parse_chunk_headers(const uint8_t *buf,
                                     int num_recs)
{
    TyRecHdr *hdrs, *rec_hdr;
    int i;

    hdrs = av_calloc(num_recs, sizeof(TyRecHdr));
    if (!hdrs)
        return NULL;

    for (i = 0; i < num_recs; i++) {
        const uint8_t *record_header = buf + (i * 16);

        rec_hdr = &hdrs[i];     /* for brevity */
        rec_hdr->rec_type = record_header[3];
        rec_hdr->subrec_type = record_header[2] & 0x0f;
        if ((record_header[0] & 0x80) == 0x80) {
            uint8_t b1, b2;

            /* marker bit 2 set, so read extended data */
            b1 = (((record_header[0] & 0x0f) << 4) |
                  ((record_header[1] & 0xf0) >> 4));
            b2 = (((record_header[1] & 0x0f) << 4) |
                  ((record_header[2] & 0xf0) >> 4));

            rec_hdr->ex[0] = b1;
            rec_hdr->ex[1] = b2;
            rec_hdr->rec_size = 0;
            rec_hdr->ty_pts = 0;
        } else {
            rec_hdr->rec_size = (record_header[0] << 8 |
                                 record_header[1]) << 4 |
                                (record_header[2] >> 4);
            rec_hdr->ty_pts = AV_RB64(&record_header[8]);
        }
    }
    return hdrs;
}