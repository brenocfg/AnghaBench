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
struct sbg_parser {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  lex_char (struct sbg_parser*,char) ; 
 int /*<<< orphan*/  lex_double (struct sbg_parser*,double*) ; 
 scalar_t__ scale_double (int /*<<< orphan*/ ,double,double,int*) ; 

__attribute__((used)) static int parse_volume(struct sbg_parser *p, int *vol)
{
    double v;

    if (!lex_char(p, '/'))
        return 0;
    if (!lex_double(p, &v))
        return AVERROR_INVALIDDATA;
    if (scale_double(p->log, v, 0.01, vol))
        return AVERROR(ERANGE);
    return 1;
}