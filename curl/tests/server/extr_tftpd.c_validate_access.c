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
typedef  int /*<<< orphan*/  weare ;
struct testcase {size_t bufsize; size_t rcount; long testno; scalar_t__ buffer; scalar_t__ rptr; } ;
typedef  int /*<<< orphan*/  partbuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EACCESS ; 
 int /*<<< orphan*/  ISDIGIT (char) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getpart (scalar_t__*,size_t*,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 size_t msnprintf (char*,int,char*,long) ; 
 int /*<<< orphan*/  parse_servercmd (struct testcase*) ; 
 scalar_t__ strdup (char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 
 long strtol (char*,char**,int) ; 
 char* test2file (long) ; 

__attribute__((used)) static int validate_access(struct testcase *test,
                           const char *filename, int mode)
{
  char *ptr;

  logmsg("trying to get file: %s mode %x", filename, mode);

  if(!strncmp("verifiedserver", filename, 14)) {
    char weare[128];
    size_t count = msnprintf(weare, sizeof(weare),
                             "WE ROOLZ: %ld\r\n", (long)getpid());

    logmsg("Are-we-friendly question received");
    test->buffer = strdup(weare);
    test->rptr = test->buffer; /* set read pointer */
    test->bufsize = count;    /* set total count */
    test->rcount = count;     /* set data left to read */
    return 0; /* fine */
  }

  /* find the last slash */
  ptr = strrchr(filename, '/');

  if(ptr) {
    char partbuf[80]="data";
    long partno;
    long testno;
    char *file;

    ptr++; /* skip the slash */

    /* skip all non-numericals following the slash */
    while(*ptr && !ISDIGIT(*ptr))
      ptr++;

    /* get the number */
    testno = strtol(ptr, &ptr, 10);

    if(testno > 10000) {
      partno = testno % 10000;
      testno /= 10000;
    }
    else
      partno = 0;


    logmsg("requested test number %ld part %ld", testno, partno);

    test->testno = testno;

    (void)parse_servercmd(test);

    file = test2file(testno);

    if(0 != partno)
      msnprintf(partbuf, sizeof(partbuf), "data%ld", partno);

    if(file) {
      FILE *stream = fopen(file, "rb");
      if(!stream) {
        int error = errno;
        logmsg("fopen() failed with error: %d %s", error, strerror(error));
        logmsg("Error opening file: %s", file);
        logmsg("Couldn't open test file: %s", file);
        return EACCESS;
      }
      else {
        size_t count;
        int error = getpart(&test->buffer, &count, "reply", partbuf, stream);
        fclose(stream);
        if(error) {
          logmsg("getpart() failed with error: %d", error);
          return EACCESS;
        }
        if(test->buffer) {
          test->rptr = test->buffer; /* set read pointer */
          test->bufsize = count;    /* set total count */
          test->rcount = count;     /* set data left to read */
        }
        else
          return EACCESS;
      }

    }
    else
      return EACCESS;
  }
  else {
    logmsg("no slash found in path");
    return EACCESS; /* failure */
  }

  logmsg("file opened and all is good");
  return 0;
}