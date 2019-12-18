#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* v; struct TYPE_4__* hashnext; } ;
typedef  TYPE_1__ th_edge_t ;
struct TYPE_5__ {TYPE_1__** edgehash; } ;

/* Variables and functions */
 int EDGEHASH_SIZE ; 
 TYPE_2__ thworld ; 

void TH_AddEdgeToHash(th_edge_t *edge)
{
	int hashvalue;

	hashvalue = (edge->v[0] + edge->v[1]) & (EDGEHASH_SIZE-1);
	edge->hashnext = thworld.edgehash[hashvalue];
	thworld.edgehash[hashvalue] = edge;
}