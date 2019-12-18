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
typedef  int /*<<< orphan*/  var ;
struct Doc {char const* (* name ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Doc ; 
 char const* c_str (int /*<<< orphan*/ ) ; 
 char const* stub1 () ; 
 struct Doc* type_instance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char* name(var type) {
  struct Doc* doc = type_instance(type, Doc);
  if (doc->name) { return doc->name(); }
  return c_str(type);
}