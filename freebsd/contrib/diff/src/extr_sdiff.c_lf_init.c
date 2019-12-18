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
struct line_filter {char* bufpos; char* buffer; char* buflim; int /*<<< orphan*/ * infile; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ SDIFF_BUFSIZE ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
lf_init (struct line_filter *lf, FILE *infile)
{
  lf->infile = infile;
  lf->bufpos = lf->buffer = lf->buflim = xmalloc (SDIFF_BUFSIZE + 1);
  lf->buflim[0] = '\n';
}