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
typedef  int /*<<< orphan*/ * var ;
struct Exception {int /*<<< orphan*/  msg; int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  Exception ; 
 int /*<<< orphan*/ * Exception_Buffer (struct Exception*) ; 
 int /*<<< orphan*/  Exception_Error (struct Exception*) ; 
 int Exception_Len (struct Exception*) ; 
 struct Exception* current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_to_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

var exception_throw(var obj, const char* fmt, var args) {

  struct Exception* e = current(Exception);
  
  e->obj = obj;
  print_to_with(e->msg, 0, fmt, args);
  
  if (Exception_Len(e) >= 1) {
    longjmp(*Exception_Buffer(e), 1);
  } else {
    Exception_Error(e);
  }
  
  return NULL;
  
}