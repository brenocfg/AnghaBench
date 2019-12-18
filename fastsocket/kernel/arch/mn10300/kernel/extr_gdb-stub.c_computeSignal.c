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
struct excep_to_sig_map {int signo; int excep; } ;
typedef  enum exception_code { ____Placeholder_exception_code } exception_code ;

/* Variables and functions */
 int SIGHUP ; 
 struct excep_to_sig_map* excep_to_sig_map ; 

__attribute__((used)) static int computeSignal(enum exception_code excep)
{
	const struct excep_to_sig_map *map;

	for (map = excep_to_sig_map; map->signo; map++)
		if (map->excep == excep)
			return map->signo;

	return SIGHUP; /* default for things we don't know about */
}