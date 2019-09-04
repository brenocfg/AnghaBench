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
typedef  int /*<<< orphan*/  logfilename ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LOGFILE ; 
 int TRUE ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int getpart (char**,size_t*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  msnprintf (char*,int,int /*<<< orphan*/ ,long) ; 
 char const* path ; 
 char* printable (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 char* serverlogfile ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 long strtol (char const*,char**,int) ; 
 char* test2file (long) ; 

int main(int argc, char *argv[])
{
  char buf[1024];
  char logfilename[256];
  FILE *stream;
  char *filename;
  int error;
  char *type1_input = NULL, *type3_input = NULL;
  char *type1_output = NULL, *type3_output = NULL;
  size_t size = 0;
  long testnum;
  const char *env;
  int arg = 1;
  const char *helper_user = "unknown";
  const char *helper_proto = "unknown";
  const char *helper_domain = "unknown";
  bool use_cached_creds = FALSE;
  char *msgbuf;

  buf[0] = '\0';

  while(argc > arg) {
    if(!strcmp("--use-cached-creds", argv[arg])) {
      use_cached_creds = TRUE;
      arg++;
    }
    else if(!strcmp("--helper-protocol", argv[arg])) {
      arg++;
      if(argc > arg)
        helper_proto = argv[arg++];
    }
    else if(!strcmp("--username", argv[arg])) {
      arg++;
      if(argc > arg)
        helper_user = argv[arg++];
    }
    else if(!strcmp("--domain", argv[arg])) {
      arg++;
      if(argc > arg)
        helper_domain = argv[arg++];
    }
    else {
      puts("Usage: fake_ntlm [option]\n"
           " --use-cached-creds\n"
           " --helper-protocol [protocol]\n"
           " --username [username]\n"
           " --domain [domain]");
      exit(1);
    }
  }

  env = getenv("CURL_NTLM_AUTH_TESTNUM");
  if(env) {
    char *endptr;
    long lnum = strtol(env, &endptr, 10);
    if((endptr != env + strlen(env)) || (lnum < 1L)) {
      fprintf(stderr, "Test number not valid in CURL_NTLM_AUTH_TESTNUM");
      exit(1);
    }
    testnum = lnum;
  }
  else {
    fprintf(stderr, "Test number not specified in CURL_NTLM_AUTH_TESTNUM");
    exit(1);
  }

  /* logmsg cannot be used until this file name is set */
  msnprintf(logfilename, sizeof(logfilename), LOGFILE, testnum);
  serverlogfile = logfilename;

  logmsg("fake_ntlm (user: %s) (proto: %s) (domain: %s) (cached creds: %s)",
         helper_user, helper_proto, helper_domain,
         (use_cached_creds) ? "yes" : "no");

  env = getenv("CURL_NTLM_AUTH_SRCDIR");
  if(env) {
    path = env;
  }

  filename = test2file(testnum);
  stream = fopen(filename, "rb");
  if(!stream) {
    error = errno;
    logmsg("fopen() failed with error: %d %s", error, strerror(error));
    logmsg("Error opening file: %s", filename);
    logmsg("Couldn't open test file %ld", testnum);
    exit(1);
  }
  else {
    /* get the ntlm_auth input/output */
    error = getpart(&type1_input, &size, "ntlm_auth_type1", "input", stream);
    fclose(stream);
    if(error || size == 0) {
      logmsg("getpart() type 1 input failed with error: %d", error);
      exit(1);
    }
  }

  stream = fopen(filename, "rb");
  if(!stream) {
    error = errno;
    logmsg("fopen() failed with error: %d %s", error, strerror(error));
    logmsg("Error opening file: %s", filename);
    logmsg("Couldn't open test file %ld", testnum);
    exit(1);
  }
  else {
    size = 0;
    error = getpart(&type3_input, &size, "ntlm_auth_type3", "input", stream);
    fclose(stream);
    if(error || size == 0) {
      logmsg("getpart() type 3 input failed with error: %d", error);
      exit(1);
    }
  }

  while(fgets(buf, sizeof(buf), stdin)) {
    if(strcmp(buf, type1_input) == 0) {
      stream = fopen(filename, "rb");
      if(!stream) {
        error = errno;
        logmsg("fopen() failed with error: %d %s", error, strerror(error));
        logmsg("Error opening file: %s", filename);
        logmsg("Couldn't open test file %ld", testnum);
        exit(1);
      }
      else {
        size = 0;
        error = getpart(&type1_output, &size, "ntlm_auth_type1", "output",
                        stream);
        fclose(stream);
        if(error || size == 0) {
          logmsg("getpart() type 1 output failed with error: %d", error);
          exit(1);
        }
      }
      printf("%s", type1_output);
      fflush(stdout);
    }
    else if(strncmp(buf, type3_input, strlen(type3_input)) == 0) {
      stream = fopen(filename, "rb");
      if(!stream) {
        error = errno;
        logmsg("fopen() failed with error: %d %s", error, strerror(error));
        logmsg("Error opening file: %s", filename);
        logmsg("Couldn't open test file %ld", testnum);
        exit(1);
      }
      else {
        size = 0;
        error = getpart(&type3_output, &size, "ntlm_auth_type3", "output",
                        stream);
        fclose(stream);
        if(error || size == 0) {
          logmsg("getpart() type 3 output failed with error: %d", error);
          exit(1);
        }
      }
      printf("%s", type3_output);
      fflush(stdout);
    }
    else {
      printf("Unknown request\n");
      msgbuf = printable(buf, 0);
      if(msgbuf) {
        logmsg("invalid input: '%s'\n", msgbuf);
        free(msgbuf);
      }
      else
        logmsg("OOM formatting invalid input: '%s'\n", buf);
      exit(1);
    }
  }
  logmsg("Exit");
  return 1;
}