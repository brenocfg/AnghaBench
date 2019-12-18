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
struct TYPE_3__ {int /*<<< orphan*/  env; scalar_t__ json; } ;
typedef  TYPE_1__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLE_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSONSAX_INVALID_VALUE ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null ; 
 int /*<<< orphan*/  strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static void jsonx_parse_null(state_t* state)
{
   if ( !strncmp( state->json + 1, "ull", 3 ) ) /* we're sure the current character is a 'n' */
   {
      state->json += 4;
      HANDLE_0( null );
   }
   else
      longjmp( state->env, JSONSAX_INVALID_VALUE );
}