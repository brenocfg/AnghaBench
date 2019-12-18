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
struct TYPE_3__ {struct TYPE_3__* nextentry; scalar_t__ name; } ;
typedef  TYPE_1__ am_entry3 ;

/* Variables and functions */
 scalar_t__ STREQ (char*,scalar_t__) ; 

__attribute__((used)) static int
key_already_in_chain3(char *keyname, const am_entry3 *chain)
{
  const am_entry3 *tmpchain = chain;

  while (tmpchain) {
    if (keyname && tmpchain->name && STREQ(keyname, tmpchain->name))
        return 1;
    tmpchain = tmpchain->nextentry;
  }

  return 0;
}