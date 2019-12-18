#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct charset {char const* name; int valid_host_charset; int (* host_char_print_literally ) (void*,int) ;int (* target_char_to_control_char ) (void*,int,int*) ;void* target_char_to_control_char_baton; void* host_char_print_literally_baton; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct charset*,int /*<<< orphan*/ ,int) ; 
 struct charset* xmalloc (int) ; 

__attribute__((used)) static struct charset *
simple_charset (const char *name,
                int valid_host_charset,
                int (*host_char_print_literally) (void *baton, int host_char),
                void *host_char_print_literally_baton,
                int (*target_char_to_control_char) (void *baton,
                                                    int target_char,
                                                    int *target_ctrl_char),
                void *target_char_to_control_char_baton)
{
  struct charset *cs = xmalloc (sizeof (*cs));

  memset (cs, 0, sizeof (*cs));
  cs->name = name;
  cs->valid_host_charset = valid_host_charset;
  cs->host_char_print_literally = host_char_print_literally;
  cs->host_char_print_literally_baton = host_char_print_literally_baton;
  cs->target_char_to_control_char = target_char_to_control_char;
  cs->target_char_to_control_char_baton = target_char_to_control_char_baton;

  return cs;
}