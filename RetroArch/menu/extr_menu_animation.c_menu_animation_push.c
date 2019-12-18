#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tween {scalar_t__ duration; scalar_t__ initial_value; scalar_t__ target_value; scalar_t__* subject; int deleted; int /*<<< orphan*/ * easing; int /*<<< orphan*/  userdata; int /*<<< orphan*/  cb; int /*<<< orphan*/  tag; scalar_t__ running_since; } ;
struct TYPE_4__ {scalar_t__ duration; scalar_t__* subject; scalar_t__ target_value; int easing_enum; int /*<<< orphan*/  userdata; int /*<<< orphan*/  cb; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ menu_animation_ctx_entry_t ;
struct TYPE_5__ {int initialized; int /*<<< orphan*/  list; int /*<<< orphan*/  pending; scalar_t__ in_update; } ;

/* Variables and functions */
#define  EASING_IN_BOUNCE 160 
#define  EASING_IN_CIRC 159 
#define  EASING_IN_CUBIC 158 
#define  EASING_IN_EXPO 157 
#define  EASING_IN_OUT_BOUNCE 156 
#define  EASING_IN_OUT_CIRC 155 
#define  EASING_IN_OUT_CUBIC 154 
#define  EASING_IN_OUT_EXPO 153 
#define  EASING_IN_OUT_QUAD 152 
#define  EASING_IN_OUT_QUART 151 
#define  EASING_IN_OUT_QUINT 150 
#define  EASING_IN_OUT_SINE 149 
#define  EASING_IN_QUAD 148 
#define  EASING_IN_QUART 147 
#define  EASING_IN_QUINT 146 
#define  EASING_IN_SINE 145 
#define  EASING_LINEAR 144 
#define  EASING_OUT_BOUNCE 143 
#define  EASING_OUT_CIRC 142 
#define  EASING_OUT_CUBIC 141 
#define  EASING_OUT_EXPO 140 
#define  EASING_OUT_IN_BOUNCE 139 
#define  EASING_OUT_IN_CIRC 138 
#define  EASING_OUT_IN_CUBIC 137 
#define  EASING_OUT_IN_EXPO 136 
#define  EASING_OUT_IN_QUAD 135 
#define  EASING_OUT_IN_QUART 134 
#define  EASING_OUT_IN_QUINT 133 
#define  EASING_OUT_IN_SINE 132 
#define  EASING_OUT_QUAD 131 
#define  EASING_OUT_QUART 130 
#define  EASING_OUT_QUINT 129 
#define  EASING_OUT_SINE 128 
 TYPE_3__ anim ; 
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_push (int /*<<< orphan*/ ,struct tween) ; 
 int /*<<< orphan*/  easing_in_bounce ; 
 int /*<<< orphan*/  easing_in_circ ; 
 int /*<<< orphan*/  easing_in_cubic ; 
 int /*<<< orphan*/  easing_in_expo ; 
 int /*<<< orphan*/  easing_in_out_bounce ; 
 int /*<<< orphan*/  easing_in_out_circ ; 
 int /*<<< orphan*/  easing_in_out_cubic ; 
 int /*<<< orphan*/  easing_in_out_expo ; 
 int /*<<< orphan*/  easing_in_out_quad ; 
 int /*<<< orphan*/  easing_in_out_quart ; 
 int /*<<< orphan*/  easing_in_out_quint ; 
 int /*<<< orphan*/  easing_in_out_sine ; 
 int /*<<< orphan*/  easing_in_quad ; 
 int /*<<< orphan*/  easing_in_quart ; 
 int /*<<< orphan*/  easing_in_quint ; 
 int /*<<< orphan*/  easing_in_sine ; 
 int /*<<< orphan*/  easing_linear ; 
 int /*<<< orphan*/  easing_out_bounce ; 
 int /*<<< orphan*/  easing_out_circ ; 
 int /*<<< orphan*/  easing_out_cubic ; 
 int /*<<< orphan*/  easing_out_expo ; 
 int /*<<< orphan*/  easing_out_in_bounce ; 
 int /*<<< orphan*/  easing_out_in_circ ; 
 int /*<<< orphan*/  easing_out_in_cubic ; 
 int /*<<< orphan*/  easing_out_in_expo ; 
 int /*<<< orphan*/  easing_out_in_quad ; 
 int /*<<< orphan*/  easing_out_in_quart ; 
 int /*<<< orphan*/  easing_out_in_quint ; 
 int /*<<< orphan*/  easing_out_in_sine ; 
 int /*<<< orphan*/  easing_out_quad ; 
 int /*<<< orphan*/  easing_out_quart ; 
 int /*<<< orphan*/  easing_out_quint ; 
 int /*<<< orphan*/  easing_out_sine ; 

bool menu_animation_push(menu_animation_ctx_entry_t *entry)
{
   struct tween t;

   t.duration           = entry->duration;
   t.running_since      = 0;
   t.initial_value      = *entry->subject;
   t.target_value       = entry->target_value;
   t.subject            = entry->subject;
   t.tag                = entry->tag;
   t.cb                 = entry->cb;
   t.userdata           = entry->userdata;
   t.easing             = NULL;
   t.deleted            = false;

   switch (entry->easing_enum)
   {
      case EASING_LINEAR:
         t.easing       = &easing_linear;
         break;
         /* Quad */
      case EASING_IN_QUAD:
         t.easing       = &easing_in_quad;
         break;
      case EASING_OUT_QUAD:
         t.easing       = &easing_out_quad;
         break;
      case EASING_IN_OUT_QUAD:
         t.easing       = &easing_in_out_quad;
         break;
      case EASING_OUT_IN_QUAD:
         t.easing       = &easing_out_in_quad;
         break;
         /* Cubic */
      case EASING_IN_CUBIC:
         t.easing       = &easing_in_cubic;
         break;
      case EASING_OUT_CUBIC:
         t.easing       = &easing_out_cubic;
         break;
      case EASING_IN_OUT_CUBIC:
         t.easing       = &easing_in_out_cubic;
         break;
      case EASING_OUT_IN_CUBIC:
         t.easing       = &easing_out_in_cubic;
         break;
         /* Quart */
      case EASING_IN_QUART:
         t.easing       = &easing_in_quart;
         break;
      case EASING_OUT_QUART:
         t.easing       = &easing_out_quart;
         break;
      case EASING_IN_OUT_QUART:
         t.easing       = &easing_in_out_quart;
         break;
      case EASING_OUT_IN_QUART:
         t.easing       = &easing_out_in_quart;
         break;
         /* Quint */
      case EASING_IN_QUINT:
         t.easing       = &easing_in_quint;
         break;
      case EASING_OUT_QUINT:
         t.easing       = &easing_out_quint;
         break;
      case EASING_IN_OUT_QUINT:
         t.easing       = &easing_in_out_quint;
         break;
      case EASING_OUT_IN_QUINT:
         t.easing       = &easing_out_in_quint;
         break;
         /* Sine */
      case EASING_IN_SINE:
         t.easing       = &easing_in_sine;
         break;
      case EASING_OUT_SINE:
         t.easing       = &easing_out_sine;
         break;
      case EASING_IN_OUT_SINE:
         t.easing       = &easing_in_out_sine;
         break;
      case EASING_OUT_IN_SINE:
         t.easing       = &easing_out_in_sine;
         break;
         /* Expo */
      case EASING_IN_EXPO:
         t.easing       = &easing_in_expo;
         break;
      case EASING_OUT_EXPO:
         t.easing       = &easing_out_expo;
         break;
      case EASING_IN_OUT_EXPO:
         t.easing       = &easing_in_out_expo;
         break;
      case EASING_OUT_IN_EXPO:
         t.easing       = &easing_out_in_expo;
         break;
         /* Circ */
      case EASING_IN_CIRC:
         t.easing       = &easing_in_circ;
         break;
      case EASING_OUT_CIRC:
         t.easing       = &easing_out_circ;
         break;
      case EASING_IN_OUT_CIRC:
         t.easing       = &easing_in_out_circ;
         break;
      case EASING_OUT_IN_CIRC:
         t.easing       = &easing_out_in_circ;
         break;
         /* Bounce */
      case EASING_IN_BOUNCE:
         t.easing       = &easing_in_bounce;
         break;
      case EASING_OUT_BOUNCE:
         t.easing       = &easing_out_bounce;
         break;
      case EASING_IN_OUT_BOUNCE:
         t.easing       = &easing_in_out_bounce;
         break;
      case EASING_OUT_IN_BOUNCE:
         t.easing       = &easing_out_in_bounce;
         break;
      default:
         break;
   }

   /* ignore born dead tweens */
   if (!t.easing || t.duration == 0 || t.initial_value == t.target_value)
      return false;

   if (!anim.initialized)
   {
      da_init(anim.list);
      da_init(anim.pending);
      anim.initialized = true;
   }

   if (anim.in_update)
      da_push(anim.pending, t);
   else
      da_push(anim.list, t);

   return true;
}