#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; int* ptr; } ;
typedef  TYPE_1__ sb ;

/* Variables and functions */
 int get_token (int,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  macro_mri ; 
 scalar_t__ macro_strip_at ; 

__attribute__((used)) static int
get_apost_token (int idx, sb *in, sb *name, int kind)
{
  idx = get_token (idx, in, name);
  if (idx < in->len
      && in->ptr[idx] == kind
      && (! macro_mri || macro_strip_at)
      && (! macro_strip_at || kind == '@'))
    idx++;
  return idx;
}