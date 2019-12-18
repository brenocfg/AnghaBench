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
struct alias {int dummy; } ;

/* Variables and functions */
 unsigned int ATABSIZE ; 
 struct alias** atab ; 

__attribute__((used)) static struct alias **
hashalias(const char *p)
{
	unsigned int hashval;

	hashval = (unsigned char)*p << 4;
	while (*p)
		hashval+= *p++;
	return &atab[hashval % ATABSIZE];
}