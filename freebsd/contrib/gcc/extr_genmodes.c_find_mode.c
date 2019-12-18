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
struct mode_data {char const* name; } ;

/* Variables and functions */
 scalar_t__ htab_find (int /*<<< orphan*/ ,struct mode_data*) ; 
 int /*<<< orphan*/  modes_by_name ; 

__attribute__((used)) static inline struct mode_data *
find_mode (const char *name)
{
  struct mode_data key;

  key.name = name;
  return (struct mode_data *) htab_find (modes_by_name, &key);
}