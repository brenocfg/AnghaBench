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
struct TYPE_3__ {int json; int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLE_1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JSONSAX_INVALID_VALUE ; 
 int /*<<< orphan*/  boolean ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int,char*,int) ; 

__attribute__((used)) static void jsonx_parse_boolean(state_t* state)
{
   if ( !strncmp( state->json, "true", 4 ) )
   {
      state->json += 4;
      HANDLE_1( boolean, 1 );
   }
   else if ( !strncmp( state->json, "false", 5 ) )
   {
      state->json += 5;
      HANDLE_1( boolean, 0 );
   }
   else
      longjmp( state->env, JSONSAX_INVALID_VALUE );
}