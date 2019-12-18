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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ asmfile ; 
 int /*<<< orphan*/  base (int /*<<< orphan*/ ) ; 
 scalar_t__ dumpasm ; 
 int /*<<< orphan*/ * fopen (scalar_t__,char*) ; 
 scalar_t__ format (char*) ; 
 int /*<<< orphan*/  infile ; 
 int /*<<< orphan*/  mkstemps (scalar_t__,int) ; 
 scalar_t__ outfile ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ replace_suffix (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  tmpfiles ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static FILE *open_asmfile() {
    if (dumpasm) {
        asmfile = outfile ? outfile : replace_suffix(base(infile), 's');
    } else {
        asmfile = format("/tmp/8ccXXXXXX.s");
        if (!mkstemps(asmfile, 2))
            perror("mkstemps");
        vec_push(tmpfiles, asmfile);
    }
    if (!strcmp(asmfile, "-"))
        return stdout;
    FILE *fp = fopen(asmfile, "w");
    if (!fp)
        perror("fopen");
    return fp;
}