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

/* Variables and functions */
 scalar_t__ ASE_GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  s_token ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ASE_SkipEnclosingBraces( void )
{
	int indent = 0;

	while ( ASE_GetToken( qfalse ) )
	{
		if ( !strcmp( s_token, "{" ) )
		{
			indent++;
		}
		else if ( !strcmp( s_token, "}" ) )
		{
			indent--;
			if ( indent == 0 )
				break;
			else if ( indent < 0 )
				Error( "Unexpected '}'" );
		}
	}
}