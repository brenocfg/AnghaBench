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
typedef  int /*<<< orphan*/  COST_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  L1 ; 
 int /*<<< orphan*/  MASKED ; 
 int /*<<< orphan*/  SEG ; 
 int /*<<< orphan*/  SMOOTH ; 
 int /*<<< orphan*/  SSE ; 
 int /*<<< orphan*/  WGAN ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

COST_TYPE get_cost_type(char *s)
{
    if (strcmp(s, "seg")==0) return SEG;
    if (strcmp(s, "sse")==0) return SSE;
    if (strcmp(s, "masked")==0) return MASKED;
    if (strcmp(s, "smooth")==0) return SMOOTH;
    if (strcmp(s, "L1")==0) return L1;
    if (strcmp(s, "wgan")==0) return WGAN;
    fprintf(stderr, "Couldn't find cost type %s, going with SSE\n", s);
    return SSE;
}