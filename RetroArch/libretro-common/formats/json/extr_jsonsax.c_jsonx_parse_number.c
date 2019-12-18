#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* json; int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLE_2 (char const*,char const*,int) ; 
 int /*<<< orphan*/  JSONSAX_INVALID_VALUE ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_digits (TYPE_1__*) ; 

__attribute__((used)) static void jsonx_parse_number(state_t* state)
{
   const char* number = state->json;

   if ( *state->json == '-' )
      state->json++;

   if ( !isdigit( (unsigned char)*state->json ) )
      longjmp( state->env, JSONSAX_INVALID_VALUE );

   skip_digits( state );

   if ( *state->json == '.' )
   {
      state->json++;

      if ( !isdigit( (unsigned char)*state->json ) )
         longjmp( state->env, JSONSAX_INVALID_VALUE );

      skip_digits( state );
   }

   if ( *state->json == 'e' || *state->json == 'E' )
   {
      state->json++;

      if ( *state->json == '-' || *state->json == '+' )
         state->json++;

      if ( !isdigit( (unsigned char)*state->json ) )
         longjmp( state->env, JSONSAX_INVALID_VALUE );

      skip_digits( state );
   }

   HANDLE_2( number, number, state->json - number );
}