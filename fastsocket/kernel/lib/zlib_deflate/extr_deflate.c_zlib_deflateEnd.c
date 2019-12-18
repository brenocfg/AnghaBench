#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct TYPE_5__ {int status; } ;
typedef  TYPE_2__ deflate_state ;
struct TYPE_4__ {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int BUSY_STATE ; 
 int FINISH_STATE ; 
 int INIT_STATE ; 
 int Z_DATA_ERROR ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 

int zlib_deflateEnd(
	z_streamp strm
)
{
    int status;
    deflate_state *s;

    if (strm == NULL || strm->state == NULL) return Z_STREAM_ERROR;
    s = (deflate_state *) strm->state;

    status = s->status;
    if (status != INIT_STATE && status != BUSY_STATE &&
	status != FINISH_STATE) {
      return Z_STREAM_ERROR;
    }

    strm->state = NULL;

    return status == BUSY_STATE ? Z_DATA_ERROR : Z_OK;
}