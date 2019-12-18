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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ max_seq_num; scalar_t__ probation; scalar_t__ bad_seq; int /*<<< orphan*/  received; } ;
typedef  TYPE_1__ VC_CONTAINER_TRACK_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ MAX_DROPOUT ; 
 scalar_t__ MAX_MISORDER ; 
 scalar_t__ MIN_SEQUENTIAL ; 
 int RTP_SEQ_MOD ; 
 int /*<<< orphan*/  init_sequence_number (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static bool update_sequence_number(VC_CONTAINER_TRACK_MODULE_T *t_module,
      uint16_t seq)
{
   uint16_t udelta = seq - t_module->max_seq_num;

   /* NOTE: This source is derived from the example code in RFC3550, section A.1 */

   /* Source is not valid until MIN_SEQUENTIAL packets with
    * sequential sequence numbers have been received. */
   if (t_module->probation)
   {
      /* packet is in sequence */
      if (seq == t_module->max_seq_num + 1)
      {
         t_module->probation--;
         t_module->max_seq_num = seq;
         LOG_INFO(0, "RTP: Probation, %u more packet(s) to go at 0x%4.4hx", t_module->probation, seq);

         if (!t_module->probation)
         {
            init_sequence_number(t_module, seq);
            t_module->received++;
            return 1;
         }
      } else {
         t_module->probation = MIN_SEQUENTIAL - 1;
         t_module->max_seq_num = seq;
         LOG_INFO(0, "RTP: Probation reset, wait for %u packet(s) at 0x%4.4hx", t_module->probation, seq);
      }
      return 0;
   } else if (udelta < MAX_DROPOUT)
   {
      if (!udelta)
      {
         /* Duplicate packet, drop it */
         LOG_INFO(0, "RTP: Drop duplicate packet at 0x%4.4hx", seq);
         return 0;
      }
      if (udelta > 1)
      {
         LOG_INFO(0, "RTP: Jumped by %hu packets to 0x%4.4hx", udelta, seq);
      }
      /* in order, with permissible gap */
      t_module->max_seq_num = seq;
   } else
#if (MAX_MISORDER != 0)
      /* When MAX_MISORDER is zero, always treat as out of order */
      if (udelta <= RTP_SEQ_MOD - MAX_MISORDER)
#endif
      {
         /* the sequence number made a very large jump */
         if (seq == t_module->bad_seq)
         {
            LOG_INFO(0, "RTP: Misorder restart at 0x%4.4hx", seq);
            /* Two sequential packets -- assume that the other side
             * restarted without telling us so just re-sync
             * (i.e., pretend this was the first packet). */
            init_sequence_number(t_module, seq);
         } else {
            LOG_INFO(0, "RTP: Misorder at 0x%4.4hx, expected 0x%4.4hx", seq, t_module->max_seq_num);
            t_module->bad_seq = (seq + 1) & (RTP_SEQ_MOD-1);
            return 0;
         }
      }
#if (MAX_MISORDER != 0)
   else {
      /* duplicate or reordered packet */

      /* TODO: handle out of order packets */
   }
#endif
   t_module->received++;
   return 1;
}