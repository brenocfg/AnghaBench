#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * v1_codebook; } ;
typedef  TYPE_1__ strip_info ;
struct TYPE_6__ {scalar_t__ pix_fmt; } ;
typedef  TYPE_2__ CinepakEncContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_RGB24 ; 

__attribute__((used)) static void decode_v1_vector(CinepakEncContext *s, uint8_t *data[4],
                             int linesize[4], int v1_vector, strip_info *info)
{
    int entry_size = s->pix_fmt == AV_PIX_FMT_RGB24 ? 6 : 4;

    data[0][0] =
    data[0][1] =
    data[0][    linesize[0]] =
    data[0][1 + linesize[0]] = info->v1_codebook[v1_vector * entry_size];

    data[0][2] =
    data[0][3] =
    data[0][2 + linesize[0]] =
    data[0][3 + linesize[0]] = info->v1_codebook[v1_vector * entry_size + 1];

    data[0][    2 * linesize[0]] =
    data[0][1 + 2 * linesize[0]] =
    data[0][    3 * linesize[0]] =
    data[0][1 + 3 * linesize[0]] = info->v1_codebook[v1_vector * entry_size + 2];

    data[0][2 + 2 * linesize[0]] =
    data[0][3 + 2 * linesize[0]] =
    data[0][2 + 3 * linesize[0]] =
    data[0][3 + 3 * linesize[0]] = info->v1_codebook[v1_vector * entry_size + 3];

    if (s->pix_fmt == AV_PIX_FMT_RGB24) {
        data[1][0] =
        data[1][1] =
        data[1][    linesize[1]] =
        data[1][1 + linesize[1]] = info->v1_codebook[v1_vector * entry_size + 4];

        data[2][0] =
        data[2][1] =
        data[2][    linesize[2]] =
        data[2][1 + linesize[2]] = info->v1_codebook[v1_vector * entry_size + 5];
    }
}