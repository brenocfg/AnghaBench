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
typedef  int /*<<< orphan*/  vec_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MatchToken (char*) ; 
 int /*<<< orphan*/  atof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  token ; 

void Parse1DMatrix (int x, vec_t *m) {
	int		i;

	MatchToken( "(" );

	for (i = 0 ; i < x ; i++) {
		GetToken( qfalse );
		m[i] = atof(token);
	}

	MatchToken( ")" );
}