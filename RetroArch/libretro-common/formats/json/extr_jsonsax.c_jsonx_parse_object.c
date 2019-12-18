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
 int /*<<< orphan*/  HANDLE_2 (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  JSONSAX_MISSING_KEY ; 
 int /*<<< orphan*/  JSONSAX_MISSING_VALUE ; 
 int /*<<< orphan*/  JSONSAX_UNTERMINATED_KEY ; 
 int /*<<< orphan*/  JSONSAX_UNTERMINATED_OBJECT ; 
 int /*<<< orphan*/  end_object ; 
 int /*<<< orphan*/  jsonx_parse_value (TYPE_1__*) ; 
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_spaces (TYPE_1__*) ; 
 int /*<<< orphan*/  start_object ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void jsonx_parse_object( state_t* state )
{
   state->json++; /* we're sure the current character is a '{' */
   skip_spaces( state );
   HANDLE_0( start_object );

   while ( *state->json != '}' )
   {
      const char *name = NULL;
      if ( *state->json != '"' )
         longjmp( state->env, JSONSAX_MISSING_KEY );

      name = ++state->json;

      for ( ;; )
      {
         const char* quote = strchr( state->json, '"' );

         if ( !quote )
            longjmp( state->env, JSONSAX_UNTERMINATED_KEY );

         state->json = quote + 1;

         if ( quote[ -1 ] != '\\' )
            break;
      }

      HANDLE_2( key, name, state->json - name - 1 );
      skip_spaces( state );

      if ( *state->json != ':' )
         longjmp( state->env, JSONSAX_MISSING_VALUE );

      state->json++;
      skip_spaces( state );
      jsonx_parse_value( state );
      skip_spaces( state );

      if ( *state->json != ',' )
         break;

      state->json++;
      skip_spaces( state );
   }

   if ( *state->json != '}' )
      longjmp( state->env, JSONSAX_UNTERMINATED_OBJECT );

   state->json++;
   HANDLE_0( end_object );
}