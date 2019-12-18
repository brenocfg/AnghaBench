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
struct TYPE_3__ {size_t len; int type_enum; scalar_t__ str; int /*<<< orphan*/  s; int /*<<< orphan*/  idx; scalar_t__ spacer; int /*<<< orphan*/  selected; } ;
typedef  TYPE_1__ menu_animation_ctx_ticker_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX_LENGTH ; 
#define  TICKER_TYPE_BOUNCE 129 
#define  TICKER_TYPE_LOOP 128 
 int /*<<< orphan*/  build_ticker_loop_string (scalar_t__,scalar_t__,size_t,size_t,size_t,size_t,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_animation_ticker_generic (int /*<<< orphan*/ ,int,size_t*,size_t*) ; 
 int /*<<< orphan*/  menu_animation_ticker_loop (int /*<<< orphan*/ ,int,size_t,size_t,size_t*,size_t*,size_t*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int ticker_is_active ; 
 scalar_t__ ticker_spacer_default ; 
 int /*<<< orphan*/  utf8cpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 size_t utf8len (scalar_t__) ; 
 scalar_t__ utf8skip (scalar_t__,size_t) ; 

bool menu_animation_ticker(menu_animation_ctx_ticker_t *ticker)
{
   size_t str_len = utf8len(ticker->str);

   if (!ticker->spacer)
      ticker->spacer = ticker_spacer_default;

   if ((size_t)str_len <= ticker->len)
   {
      utf8cpy(ticker->s,
            PATH_MAX_LENGTH,
            ticker->str,
            ticker->len);
      return false;
   }

   if (!ticker->selected)
   {
      utf8cpy(ticker->s,
            PATH_MAX_LENGTH, ticker->str, ticker->len - 3);
      strlcat(ticker->s, "...", ticker->len);
      return false;
   }

   /* Note: If we reach this point then str_len > ticker->len
    * (previously had an unecessary 'if (str_len > ticker->len)'
    * check here...) */
   switch (ticker->type_enum)
   {
      case TICKER_TYPE_LOOP:
      {
         size_t offset1, offset2, offset3;
         size_t width1, width2, width3;
         
         menu_animation_ticker_loop(
               ticker->idx,
               ticker->len,
               str_len, utf8len(ticker->spacer),
               &offset1, &width1,
               &offset2, &width2,
               &offset3, &width3);
         
         build_ticker_loop_string(
               ticker->str, ticker->spacer,
               offset1, width1,
               offset2, width2,
               offset3, width3,
               ticker->s, PATH_MAX_LENGTH);
         
         break;
      }
      case TICKER_TYPE_BOUNCE:
      default:
      {
         size_t offset  = 0;
         
         menu_animation_ticker_generic(
               ticker->idx,
               ticker->len,
               &offset,
               &str_len);
         
         utf8cpy(
               ticker->s,
               PATH_MAX_LENGTH,
               utf8skip(ticker->str, offset),
               str_len);
         
         break;
      }
   }

   ticker_is_active = true;

   return true;
}