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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ pix_fmt; } ;
typedef  TYPE_1__ CinepakEncContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_RGB24 ; 
 int MB_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void copy_mb(CinepakEncContext *s,
                    uint8_t *a_data[4], int a_linesize[4],
                    uint8_t *b_data[4], int b_linesize[4])
{
    int y, p;

    for (y = 0; y < MB_SIZE; y++)
        memcpy(a_data[0] + y * a_linesize[0], b_data[0] + y * b_linesize[0],
               MB_SIZE);

    if (s->pix_fmt == AV_PIX_FMT_RGB24) {
        for (p = 1; p <= 2; p++)
            for (y = 0; y < MB_SIZE / 2; y++)
                memcpy(a_data[p] + y * a_linesize[p],
                       b_data[p] + y * b_linesize[p],
                       MB_SIZE / 2);
    }
}