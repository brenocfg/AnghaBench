#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_6__ {int oidlen; scalar_t__* oid; } ;
typedef  TYPE_1__ SmiNode ;

/* Variables and functions */
 int close_node (int,int) ; 
 int cut ; 
 int /*<<< orphan*/  pindent (int) ; 
 int /*<<< orphan*/  print_name (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* smiGetNodeByOID (int,scalar_t__*) ; 

__attribute__((used)) static u_int
open_node(const SmiNode *n, u_int level, SmiNode **last)
{
	SmiNode *n1;
	u_int i;

	if (*last != NULL) {
		for (i = 0; i < (*last)->oidlen - 1; i++) {
			if (i >= n->oidlen) {
				level = close_node((*last)->oidlen -
				    n->oidlen, level);
				break;
			}
			if ((*last)->oid[i] != n->oid[i])
				break;
		}
		if (i < (*last)->oidlen - 1)
			level = close_node((*last)->oidlen - 1 - i,
			    level - 1) + 1;
	}

	while (level < n->oidlen - 1) {
		if (level >= cut) {
			n1 = smiGetNodeByOID(level + 1, n->oid);
			if (n1 == NULL)
				continue;
			pindent(level);
			printf("(%u", n->oid[level]);
			printf(" ");
			print_name(n1);
			printf("\n");
		}
		level++;
	}
	return (level);
}