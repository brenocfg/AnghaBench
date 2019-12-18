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
typedef  int /*<<< orphan*/  ogg_stream_state ;
struct TYPE_5__ {int /*<<< orphan*/  granulepos; int /*<<< orphan*/  e_o_s; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_1__ ogg_packet ;
struct TYPE_6__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  TYPE_2__ ogg_iovec_t ;

/* Variables and functions */
 int ogg_stream_iovecin (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ogg_stream_packetin(ogg_stream_state *os,ogg_packet *op){
  ogg_iovec_t iov;
  iov.iov_base = op->packet;
  iov.iov_len = op->bytes;
  return ogg_stream_iovecin(os, &iov, 1, op->e_o_s, op->granulepos);
}