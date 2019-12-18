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
typedef  scalar_t__ FLOAT ;

/* Variables and functions */
 scalar_t__ I ; 
 int /*<<< orphan*/  IsYeqX () ; 
 scalar_t__ M ; 
 int /*<<< orphan*/  POW (int,scalar_t__) ; 
 scalar_t__ Q ; 
 int W ; 
 int X ; 
 int /*<<< orphan*/  Y ; 
 int Z ; 

SR3980()
{
	do {
		Q = (FLOAT) I;
		Y = POW(Z, Q);
		IsYeqX();
		if (++I > M) break;
		X = Z * X;
		} while ( X < W );
	}