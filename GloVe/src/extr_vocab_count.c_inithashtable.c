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
typedef  int /*<<< orphan*/  HASHREC ;

/* Variables and functions */
 int TSIZE ; 
 scalar_t__ malloc (int) ; 

HASHREC ** inithashtable() {
    int i;
    HASHREC **ht;
    ht = (HASHREC **) malloc( sizeof(HASHREC *) * TSIZE );
    for (i = 0; i < TSIZE; i++) ht[i] = (HASHREC *) NULL;
    return ht;
}