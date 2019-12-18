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
struct stub_state {int* stack; int i; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void stub_state_post_print(struct stub_state *s)
{
   switch (s->stack[s->i - 1])
   {
      case 1:
         if (s->stack[s->i] % 2 == 0)
         {
            printf(": ");
            s->stack[s->i]--;
         }
         else if (s->stack[s->i] == 1)
         {
            printf("}");
            s->i -= 2;
            stub_state_post_print(s);
         }
         else
         {
            printf(", ");
            s->stack[s->i]--;
         }
         break;
      case 2:
         if (s->stack[s->i] == 1)
         {
            printf("]");
            s->i -= 2;
            stub_state_post_print(s);
         }
         else
         {
            printf(", ");
            s->stack[s->i]--;
         }
         break;
   }
}