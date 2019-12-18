#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* json; int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ state_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSONSAX_INVALID_VALUE ; 
 int /*<<< orphan*/  jsonx_parse_array (TYPE_1__*) ; 
 int /*<<< orphan*/  jsonx_parse_boolean (TYPE_1__*) ; 
 int /*<<< orphan*/  jsonx_parse_null (TYPE_1__*) ; 
 int /*<<< orphan*/  jsonx_parse_number (TYPE_1__*) ; 
 int /*<<< orphan*/  jsonx_parse_object (TYPE_1__*) ; 
 int /*<<< orphan*/  jsonx_parse_string (TYPE_1__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_spaces (TYPE_1__*) ; 

__attribute__((used)) static void jsonx_parse_value(state_t* state)
{
   skip_spaces( state );

   switch ( *state->json )
   {
      case '{':
         jsonx_parse_object(state);
         break;
      case '[':
         jsonx_parse_array( state );
         break;
      case '"':
         jsonx_parse_string( state );
         break;
      case 't':
      case 'f':
         jsonx_parse_boolean( state );
         break;
      case 'n':
         jsonx_parse_null( state );
         break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '-':
         jsonx_parse_number( state );
         break;

      default:
         longjmp( state->env, JSONSAX_INVALID_VALUE );
   }
}