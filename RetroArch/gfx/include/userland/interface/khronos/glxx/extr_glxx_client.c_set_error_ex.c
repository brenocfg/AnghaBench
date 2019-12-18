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
struct TYPE_3__ {scalar_t__ error; } ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_1__ GLXX_CLIENT_STATE_T ;

/* Variables and functions */
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  khrn_error_assist (scalar_t__,char const*) ; 

__attribute__((used)) static void set_error_ex(GLXX_CLIENT_STATE_T *state, GLenum error, const char *func)
{
   khrn_error_assist(error, func);

   if (state->error == GL_NO_ERROR)
      state->error = error;
}