#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* next; } ;
struct TYPE_7__ {scalar_t__ kind; int user_conv_p; TYPE_1__ u; } ;
typedef  TYPE_2__ conversion ;

/* Variables and functions */
 scalar_t__ ck_identity ; 
 scalar_t__ ck_user ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static conversion *
merge_conversion_sequences (conversion *user_seq, conversion *std_seq)
{
  conversion **t;

  gcc_assert (user_seq->kind == ck_user);

  /* Find the end of the second conversion sequence.  */
  t = &(std_seq);
  while ((*t)->kind != ck_identity)
    t = &((*t)->u.next);

  /* Replace the identity conversion with the user conversion
     sequence.  */
  *t = user_seq;

  /* The entire sequence is a user-conversion sequence.  */
  std_seq->user_conv_p = true;

  return std_seq;
}