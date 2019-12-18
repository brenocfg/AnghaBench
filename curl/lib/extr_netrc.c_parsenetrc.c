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
typedef  int /*<<< orphan*/  netrcbuffer ;
typedef  enum host_lookup_state { ____Placeholder_host_lookup_state } host_lookup_state ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGASSERT (char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  FOPEN_READTEXT ; 
#define  HOSTFOUND 130 
#define  HOSTVALID 129 
 int NETRC_FAILED ; 
 int NETRC_FILE_MISSING ; 
 int NETRC_SUCCESS ; 
#define  NOTHING 128 
 int TRUE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int strcasecompare (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int parsenetrc(const char *host,
                      char **loginp,
                      char **passwordp,
                      bool *login_changed,
                      bool *password_changed,
                      char *netrcfile)
{
  FILE *file;
  int retcode = NETRC_FILE_MISSING;
  char *login = *loginp;
  char *password = *passwordp;
  bool specific_login = (login && *login != 0);
  bool login_alloc = FALSE;
  bool password_alloc = FALSE;
  enum host_lookup_state state = NOTHING;

  char state_login = 0;      /* Found a login keyword */
  char state_password = 0;   /* Found a password keyword */
  int state_our_login = FALSE;  /* With specific_login, found *our* login
                                   name */

  DEBUGASSERT(netrcfile);

  file = fopen(netrcfile, FOPEN_READTEXT);
  if(file) {
    char *tok;
    char *tok_buf;
    bool done = FALSE;
    char netrcbuffer[4096];
    int  netrcbuffsize = (int)sizeof(netrcbuffer);

    while(!done && fgets(netrcbuffer, netrcbuffsize, file)) {
      tok = strtok_r(netrcbuffer, " \t\n", &tok_buf);
      if(tok && *tok == '#')
        /* treat an initial hash as a comment line */
        continue;
      while(tok) {

        if((login && *login) && (password && *password)) {
          done = TRUE;
          break;
        }

        switch(state) {
        case NOTHING:
          if(strcasecompare("machine", tok)) {
            /* the next tok is the machine name, this is in itself the
               delimiter that starts the stuff entered for this machine,
               after this we need to search for 'login' and
               'password'. */
            state = HOSTFOUND;
          }
          else if(strcasecompare("default", tok)) {
            state = HOSTVALID;
            retcode = NETRC_SUCCESS; /* we did find our host */
          }
          break;
        case HOSTFOUND:
          if(strcasecompare(host, tok)) {
            /* and yes, this is our host! */
            state = HOSTVALID;
            retcode = NETRC_SUCCESS; /* we did find our host */
          }
          else
            /* not our host */
            state = NOTHING;
          break;
        case HOSTVALID:
          /* we are now parsing sub-keywords concerning "our" host */
          if(state_login) {
            if(specific_login) {
              state_our_login = strcasecompare(login, tok);
            }
            else if(!login || strcmp(login, tok)) {
              if(login_alloc) {
                free(login);
                login_alloc = FALSE;
              }
              login = strdup(tok);
              if(!login) {
                retcode = NETRC_FAILED; /* allocation failed */
                goto out;
              }
              login_alloc = TRUE;
            }
            state_login = 0;
          }
          else if(state_password) {
            if((state_our_login || !specific_login)
                && (!password || strcmp(password, tok))) {
              if(password_alloc) {
                free(password);
                password_alloc = FALSE;
              }
              password = strdup(tok);
              if(!password) {
                retcode = NETRC_FAILED; /* allocation failed */
                goto out;
              }
              password_alloc = TRUE;
            }
            state_password = 0;
          }
          else if(strcasecompare("login", tok))
            state_login = 1;
          else if(strcasecompare("password", tok))
            state_password = 1;
          else if(strcasecompare("machine", tok)) {
            /* ok, there's machine here go => */
            state = HOSTFOUND;
            state_our_login = FALSE;
          }
          break;
        } /* switch (state) */

        tok = strtok_r(NULL, " \t\n", &tok_buf);
      } /* while(tok) */
    } /* while fgets() */

    out:
    if(!retcode) {
      /* success */
      *login_changed = FALSE;
      *password_changed = FALSE;
      if(login_alloc) {
        if(*loginp)
          free(*loginp);
        *loginp = login;
        *login_changed = TRUE;
      }
      if(password_alloc) {
        if(*passwordp)
          free(*passwordp);
        *passwordp = password;
        *password_changed = TRUE;
      }
    }
    else {
      if(login_alloc)
        free(login);
      if(password_alloc)
        free(password);
    }
    fclose(file);
  }

  return retcode;
}