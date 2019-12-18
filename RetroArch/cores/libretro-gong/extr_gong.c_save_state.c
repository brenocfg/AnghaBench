#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  unsigned int uint16_t ;
struct TYPE_24__ {TYPE_8__* buttons; } ;
struct TYPE_23__ {unsigned int half_transition_count; unsigned int ended_down; } ;
struct TYPE_22__ {unsigned int u; } ;
struct TYPE_21__ {unsigned int u; } ;
struct TYPE_20__ {unsigned int u; } ;
struct TYPE_19__ {unsigned int u; } ;
struct TYPE_18__ {unsigned int u; } ;
struct TYPE_17__ {unsigned int u; } ;
struct TYPE_16__ {unsigned int u; } ;
struct TYPE_15__ {unsigned int version; unsigned int player1_score; unsigned int player2_score; unsigned int is_initialized; unsigned int player2_human; TYPE_11__* player; TYPE_9__* g_input; int /*<<< orphan*/ * previnput; TYPE_7__ current_play_points; TYPE_6__ ball_speed; TYPE_5__ ball_dpy; TYPE_4__ ball_dpx; TYPE_3__ ball_py; TYPE_2__ ball_px; TYPE_1__ player2_speed; } ;
struct TYPE_13__ {int /*<<< orphan*/  u; } ;
struct TYPE_14__ {TYPE_10__ py; } ;

/* Variables and functions */
 int B_COUNT ; 
 int MAX_PLAYERS ; 
 TYPE_12__* g_state ; 
 int /*<<< orphan*/  memcpy (unsigned char*,...) ; 
 unsigned int swap_if_little16 (int /*<<< orphan*/ ) ; 
 void* swap_if_little32 (unsigned int) ; 

__attribute__((used)) static void save_state(void *data, size_t size)
{
   int i = 0;
   int j = 0;
   unsigned char *buf = (unsigned char*)data;
   unsigned version = swap_if_little32(g_state->version);
   unsigned player1_score = swap_if_little32(g_state->player1_score);
   unsigned player2_score = swap_if_little32(g_state->player2_score);
   unsigned player2_speed = swap_if_little32(g_state->player2_speed.u);
   unsigned ball_px = swap_if_little32(g_state->ball_px.u);
   unsigned ball_py = swap_if_little32(g_state->ball_py.u);
   unsigned ball_dpx = swap_if_little32(g_state->ball_dpx.u);
   unsigned ball_dpy = swap_if_little32(g_state->ball_dpy.u);
   unsigned ball_speed = swap_if_little32(g_state->ball_speed.u);
   unsigned current_play_points = swap_if_little32(g_state->current_play_points.u);
   unsigned is_initialized = g_state->is_initialized;
   unsigned player2_human = g_state->player2_human;

   (void)size;

   memcpy(buf, &version, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &player1_score, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &player2_score, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &player2_speed, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &ball_px, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &ball_py, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &ball_dpx, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &ball_dpy, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &ball_speed, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &current_play_points, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &is_initialized, sizeof(unsigned));
   buf += sizeof(unsigned);

   memcpy(buf, &player2_human, sizeof(unsigned));
   buf += sizeof(unsigned);

   /* previnput */
   for (i = 0; i < MAX_PLAYERS; i++)
   {
      uint16_t previnput = swap_if_little16(g_state->previnput[i]);
      memcpy(buf, &previnput, sizeof(uint16_t));
      buf += sizeof(uint16_t);
   }

   /* g_input */
   for (i = 0; i < MAX_PLAYERS; i++)
   {
      for (j = 0; j < B_COUNT; j++)
      {
         int half_transition_count = swap_if_little32(g_state->g_input[i].buttons[j].half_transition_count);
         unsigned ended_down = g_state->g_input[i].buttons[j].ended_down;

         memcpy(buf, &half_transition_count, sizeof(int));
         buf += sizeof(int);

         memcpy(buf, &ended_down, sizeof(unsigned));
         buf += sizeof(unsigned);
      }
   }

   /* player */
   for (i = 0; i < MAX_PLAYERS; i++)
   {
      unsigned py = swap_if_little32((unsigned)g_state->player[i].py.u);
       
      memcpy(buf, &py, sizeof(unsigned));
      buf += sizeof(uint16_t);
   }
}