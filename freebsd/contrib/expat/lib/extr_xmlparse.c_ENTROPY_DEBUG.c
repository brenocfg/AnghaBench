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
typedef  int /*<<< orphan*/  entropy ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,unsigned long,unsigned long) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const* const,char*) ; 

__attribute__((used)) static unsigned long
ENTROPY_DEBUG(const char * label, unsigned long entropy) {
  const char * const EXPAT_ENTROPY_DEBUG = getenv("EXPAT_ENTROPY_DEBUG");
  if (EXPAT_ENTROPY_DEBUG && ! strcmp(EXPAT_ENTROPY_DEBUG, "1")) {
    fprintf(stderr, "Entropy: %s --> 0x%0*lx (%lu bytes)\n",
        label,
        (int)sizeof(entropy) * 2, entropy,
        (unsigned long)sizeof(entropy));
  }
  return entropy;
}