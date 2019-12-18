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
struct TYPE_3__ {size_t bufend; int* buf; scalar_t__ bufbeg; } ;
typedef  TYPE_1__ mime_encoder_state ;

/* Variables and functions */
 scalar_t__ QP_CR ; 
 scalar_t__ QP_LF ; 
 scalar_t__* qp_class ; 

__attribute__((used)) static int qp_lookahead_eol(mime_encoder_state *st, int ateof, size_t n)
{
  n += st->bufbeg;
  if(n >= st->bufend && ateof)
    return 1;
  if(n + 2 > st->bufend)
    return ateof? 0: -1;
  if(qp_class[st->buf[n] & 0xFF] == QP_CR &&
     qp_class[st->buf[n + 1] & 0xFF] == QP_LF)
    return 1;
  return 0;
}