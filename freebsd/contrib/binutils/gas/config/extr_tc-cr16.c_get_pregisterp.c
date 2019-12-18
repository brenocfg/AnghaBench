#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  preg_val; } ;
struct TYPE_4__ {TYPE_1__ value; } ;
typedef  TYPE_2__ reg_entry ;
typedef  int /*<<< orphan*/  preg ;

/* Variables and functions */
 scalar_t__ hash_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nullpregister ; 
 int /*<<< orphan*/  pregp_hash ; 

__attribute__((used)) static preg
get_pregisterp (char *preg_name)
{
  const reg_entry *preg;

  preg = (const reg_entry *) hash_find (pregp_hash, preg_name);

  if (preg != NULL)
    return preg->value.preg_val;

  return nullpregister;
}