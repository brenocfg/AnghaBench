#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; char* comment; } ;
struct TYPE_5__ {char* name; char* comment; } ;
struct TYPE_4__ {char* name; char* comment; } ;

/* Variables and functions */
 TYPE_3__* cipher_suites ; 
 TYPE_2__* hash_functions ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* protocol_versions ; 

void
list_names(void)
{
	size_t u;

	printf("Protocol versions:\n");
	for (u = 0; protocol_versions[u].name; u ++) {
		printf("   %-8s %s\n",
			protocol_versions[u].name,
			protocol_versions[u].comment);
	}
	printf("Hash functions:\n");
	for (u = 0; hash_functions[u].name; u ++) {
		printf("   %-8s %s\n",
			hash_functions[u].name,
			hash_functions[u].comment);
	}
	printf("Cipher suites:\n");
	for (u = 0; cipher_suites[u].name; u ++) {
		printf("   %s\n        %s\n",
			cipher_suites[u].name,
			cipher_suites[u].comment);
	}
}