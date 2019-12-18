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
typedef  int uint32_t ;
struct TYPE_2__ {int in_cheevos; int in_lboards; int is_console_id; int /*<<< orphan*/  format; int /*<<< orphan*/ * field; int /*<<< orphan*/  flags; int /*<<< orphan*/  badge; int /*<<< orphan*/  created; int /*<<< orphan*/  modified; int /*<<< orphan*/  author; int /*<<< orphan*/  points; int /*<<< orphan*/  desc; int /*<<< orphan*/  title; int /*<<< orphan*/  memaddr; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ rcheevos_readud_t ;

/* Variables and functions */
#define  CHEEVOS_JSON_KEY_ACHIEVEMENTS 142 
#define  CHEEVOS_JSON_KEY_AUTHOR 141 
#define  CHEEVOS_JSON_KEY_BADGENAME 140 
#define  CHEEVOS_JSON_KEY_CONSOLE_ID 139 
#define  CHEEVOS_JSON_KEY_CREATED 138 
#define  CHEEVOS_JSON_KEY_DESCRIPTION 137 
#define  CHEEVOS_JSON_KEY_FLAGS 136 
#define  CHEEVOS_JSON_KEY_FORMAT 135 
#define  CHEEVOS_JSON_KEY_ID 134 
#define  CHEEVOS_JSON_KEY_LEADERBOARDS 133 
#define  CHEEVOS_JSON_KEY_MEM 132 
#define  CHEEVOS_JSON_KEY_MEMADDR 131 
#define  CHEEVOS_JSON_KEY_MODIFIED 130 
#define  CHEEVOS_JSON_KEY_POINTS 129 
#define  CHEEVOS_JSON_KEY_TITLE 128 
 int rcheevos_djb2 (char const*,size_t) ; 

__attribute__((used)) static int rcheevos_read_key(void* userdata,
      const char* name, size_t length)
{
   rcheevos_readud_t* ud = (rcheevos_readud_t*)userdata;

   int common           = ud->in_cheevos || ud->in_lboards;
   uint32_t hash        = rcheevos_djb2(name, length);
   ud->field            = NULL;

   switch (hash)
   {
      case CHEEVOS_JSON_KEY_ACHIEVEMENTS:
         ud->in_cheevos = 1;
         break;
      case CHEEVOS_JSON_KEY_LEADERBOARDS:
         ud->in_lboards = 1;
         break;
      case CHEEVOS_JSON_KEY_CONSOLE_ID:
         ud->is_console_id = 1;
         break;
      case CHEEVOS_JSON_KEY_ID:
         if (common)
            ud->field = &ud->id;
         break;
      case CHEEVOS_JSON_KEY_MEMADDR:
         if (ud->in_cheevos)
            ud->field = &ud->memaddr;
         break;
      case CHEEVOS_JSON_KEY_MEM:
         if (ud->in_lboards)
            ud->field = &ud->memaddr;
         break;
      case CHEEVOS_JSON_KEY_TITLE:
         if (common)
            ud->field = &ud->title;
         break;
      case CHEEVOS_JSON_KEY_DESCRIPTION:
         if (common)
            ud->field = &ud->desc;
         break;
      case CHEEVOS_JSON_KEY_POINTS:
         if (ud->in_cheevos)
            ud->field = &ud->points;
         break;
      case CHEEVOS_JSON_KEY_AUTHOR:
         if (ud->in_cheevos)
            ud->field = &ud->author;
         break;
      case CHEEVOS_JSON_KEY_MODIFIED:
         if (ud->in_cheevos)
            ud->field = &ud->modified;
         break;
      case CHEEVOS_JSON_KEY_CREATED:
         if (ud->in_cheevos)
            ud->field = &ud->created;
         break;
      case CHEEVOS_JSON_KEY_BADGENAME:
         if (ud->in_cheevos)
            ud->field = &ud->badge;
         break;
      case CHEEVOS_JSON_KEY_FLAGS:
         if (ud->in_cheevos)
            ud->field = &ud->flags;
         break;
      case CHEEVOS_JSON_KEY_FORMAT:
         if (ud->in_lboards)
            ud->field = &ud->format;
         break;
      default:
         break;
   }

   return 0;
}