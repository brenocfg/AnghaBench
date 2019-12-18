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
typedef  struct Type* var ;
struct Type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Type ; 
 int /*<<< orphan*/  Type_Builtin_Name (struct Type*) ; 
 struct Type* cast (struct Type*,int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Type_Cmp(var self, var obj) {
  struct Type* objt = cast(obj, Type);
  return strcmp(Type_Builtin_Name(self), Type_Builtin_Name(objt));
}