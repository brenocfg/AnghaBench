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
struct line_filter {char* buffer; char* bufpos; char* buflim; int /*<<< orphan*/  infile; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDIFF_BUFSIZE ; 
 int /*<<< orphan*/  checksigs () ; 
 size_t ck_fread (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
lf_refill (struct line_filter *lf)
{
  size_t s = ck_fread (lf->buffer, SDIFF_BUFSIZE, lf->infile);
  lf->bufpos = lf->buffer;
  lf->buflim = lf->buffer + s;
  lf->buflim[0] = '\n';
  checksigs ();
  return s;
}