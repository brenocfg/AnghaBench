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
typedef  void* uint16_t ;
struct TYPE_3__ {scalar_t__ received; scalar_t__ bad_seq; void* max_seq_num; void* base_seq; } ;
typedef  TYPE_1__ VC_CONTAINER_TRACK_MODULE_T ;

/* Variables and functions */
 scalar_t__ RTP_SEQ_MOD ; 

__attribute__((used)) static void init_sequence_number(VC_CONTAINER_TRACK_MODULE_T *t_module,
      uint16_t seq)
{
   t_module->base_seq = seq;
   t_module->max_seq_num = seq;
   t_module->bad_seq = RTP_SEQ_MOD + 1;   /* so seq == bad_seq is false */
   t_module->received = 0;
}