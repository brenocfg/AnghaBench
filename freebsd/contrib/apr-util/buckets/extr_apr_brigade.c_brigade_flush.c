#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ endpos; scalar_t__ curpos; } ;
struct brigade_vprintf_data_t {scalar_t__ cbuff; TYPE_1__ vbuff; int /*<<< orphan*/  ctx; int /*<<< orphan*/ * flusher; int /*<<< orphan*/  b; } ;
typedef  int /*<<< orphan*/  apr_vformatter_buff_t ;
typedef  scalar_t__ apr_status_t ;

/* Variables and functions */
 scalar_t__ APR_BUCKET_BUFF_SIZE ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_brigade_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static apr_status_t brigade_flush(apr_vformatter_buff_t *buff)
{
    /* callback function passed to ap_vformatter to be
     * called when vformatter needs to buff and
     * buff.curpos > buff.endpos
     */

    /* "downcast," have really passed a brigade_vprintf_data_t* */
    struct brigade_vprintf_data_t *vd = (struct brigade_vprintf_data_t*)buff;
    apr_status_t res = APR_SUCCESS;

    res = apr_brigade_write(vd->b, *vd->flusher, vd->ctx, vd->cbuff,
                          APR_BUCKET_BUFF_SIZE);

    if(res != APR_SUCCESS) {
      return -1;
    }

    vd->vbuff.curpos = vd->cbuff;
    vd->vbuff.endpos = vd->cbuff + APR_BUCKET_BUFF_SIZE;

    return res;
}