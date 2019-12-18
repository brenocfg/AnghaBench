#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* json; int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLE_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HANDLE_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSONSAX_UNTERMINATED_ARRAY ; 
 int /*<<< orphan*/  array_index ; 
 int /*<<< orphan*/  end_array ; 
 int /*<<< orphan*/  jsonx_parse_value (TYPE_1__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_spaces (TYPE_1__*) ; 
 int /*<<< orphan*/  start_array ; 

__attribute__((used)) static void jsonx_parse_array(state_t* state)
{
   unsigned int ndx = 0;

   state->json++; /* we're sure the current character is a '[' */
   skip_spaces( state );
   HANDLE_0( start_array );

   while ( *state->json != ']' )
   {
      HANDLE_1( array_index, ndx++ );
      jsonx_parse_value( state );
      skip_spaces( state );

      if ( *state->json != ',' )
         break;

      state->json++;
      skip_spaces( state );
   }

   if ( *state->json != ']' )
      longjmp( state->env, JSONSAX_UNTERMINATED_ARRAY );

   state->json++;
   HANDLE_0( end_array );
}