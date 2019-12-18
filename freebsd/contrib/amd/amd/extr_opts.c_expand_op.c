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
typedef  int /*<<< orphan*/  xbuf ;
struct opt {int nlen; char** sel_p; char** optp; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ BUFSPACE (char*,int) ; 
 int /*<<< orphan*/  D_STR ; 
 char* EXPAND_ERROR ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int NLEN ; 
 scalar_t__ STREQ (scalar_t__,char*) ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_USER ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  normalize_slash (char*) ; 
 struct opt* opt_fields ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,char*,char*,char*) ; 
 char* xstrdup (char*) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,int) ; 

__attribute__((used)) static char *
expand_op(char *opt, int sel_p)
{
#define EXPAND_ERROR "No space to expand \"%s\""
  char expbuf[MAXPATHLEN + 1];
  char nbuf[NLEN + 1];
  char *ep = expbuf;
  char *cp = opt;
  char *dp;
  struct opt *op;
  char *cp_orig = opt;

  while ((dp = strchr(cp, '$'))) {
    char ch;
    /*
     * First copy up to the $
     */
    {
      int len = dp - cp;

      if (len > 0) {
	if (BUFSPACE(ep, len)) {
	  /*
	   * We use strncpy (not xstrlcpy) because 'ep' relies on its
	   * semantics.  BUFSPACE guarantees that ep can hold len.
	   */
	  strncpy(ep, cp, len);
	  ep += len;
	} else {
	  plog(XLOG_ERROR, EXPAND_ERROR, opt);
	  goto out;
	}
      }
    }

    cp = dp + 1;
    ch = *cp++;
    if (ch == '$') {
      if (BUFSPACE(ep, 1)) {
	*ep++ = '$';
      } else {
	plog(XLOG_ERROR, EXPAND_ERROR, opt);
	goto out;
      }
    } else if (ch == '{') {
      /* Expansion... */
      enum {
	E_All, E_Dir, E_File, E_Domain, E_Host
      } todo;
      /*
       * Find closing brace
       */
      char *br_p = strchr(cp, '}');
      int len;

      /*
       * Check we found it
       */
      if (!br_p) {
	/*
	 * Just give up
	 */
	plog(XLOG_USER, "No closing '}' in \"%s\"", opt);
	goto out;
      }
      len = br_p - cp;

      /*
       * Figure out which part of the variable to grab.
       */
      if (*cp == '/') {
	/*
	 * Just take the last component
	 */
	todo = E_File;
	cp++;
	--len;
      } else if (*(br_p-1) == '/') {
	/*
	 * Take all but the last component
	 */
	todo = E_Dir;
	--len;
      } else if (*cp == '.') {
	/*
	 * Take domain name
	 */
	todo = E_Domain;
	cp++;
	--len;
      } else if (*(br_p-1) == '.') {
	/*
	 * Take host name
	 */
	todo = E_Host;
	--len;
      } else {
	/*
	 * Take the whole lot
	 */
	todo = E_All;
      }

      /*
       * Truncate if too long.  Since it won't
       * match anyway it doesn't matter that
       * it has been cut short.
       */
      if (len > NLEN)
	len = NLEN;

      /*
       * Put the string into another buffer so
       * we can do comparisons.
       *
       * We use strncpy here (not xstrlcpy) because the dest is meant
       * to be truncated and we don't want to log it as an error.  The
       * use of the BUFSPACE macro above guarantees the safe use of
       * strncpy with nbuf.
       */
      strncpy(nbuf, cp, len);
      nbuf[len] = '\0';

      /*
       * Advance cp
       */
      cp = br_p + 1;

      /*
       * Search the option array
       */
      for (op = opt_fields; op->name; op++) {
	/*
	 * Check for match
	 */
	if (len == op->nlen && STREQ(op->name, nbuf)) {
	  char xbuf[NLEN + 3];
	  char *val;
	  /*
	   * Found expansion.  Copy
	   * the correct value field.
	   */
	  if (!(!op->sel_p == !sel_p)) {
	    /*
	     * Copy the string across unexpanded
	     */
	    xsnprintf(xbuf, sizeof(xbuf), "${%s%s%s}",
		      todo == E_File ? "/" :
		      todo == E_Domain ? "." : "",
		      nbuf,
		      todo == E_Dir ? "/" :
		      todo == E_Host ? "." : "");
	    val = xbuf;
	    /*
	     * Make sure expansion doesn't
	     * munge the value!
	     */
	    todo = E_All;
	  } else if (op->sel_p) {
	    val = *op->sel_p;
	  } else {
	    val = *op->optp;
	  }

	  if (val) {
	    /*
	     * Do expansion:
	     * ${/var} means take just the last part
	     * ${var/} means take all but the last part
	     * ${.var} means take all but first part
	     * ${var.} means take just the first part
	     * ${var} means take the whole lot
	     */
	    int vlen = strlen(val);
	    char *vptr = val;
	    switch (todo) {
	    case E_Dir:
	      vptr = strrchr(val, '/');
	      if (vptr)
		vlen = vptr - val;
	      vptr = val;
	      break;
	    case E_File:
	      vptr = strrchr(val, '/');
	      if (vptr) {
		vptr++;
		vlen = strlen(vptr);
	      } else
		vptr = val;
	      break;
	    case E_Domain:
	      vptr = strchr(val, '.');
	      if (vptr) {
		vptr++;
		vlen = strlen(vptr);
	      } else {
		vptr = "";
		vlen = 0;
	      }
	      break;
	    case E_Host:
	      vptr = strchr(val, '.');
	      if (vptr)
		vlen = vptr - val;
	      vptr = val;
	      break;
	    case E_All:
	      break;
	    }

	    if (BUFSPACE(ep, vlen+1)) {
	      /*
	       * Don't call xstrlcpy() to truncate a string here.  It causes
	       * spurious xstrlcpy() syslog() errors.  Use memcpy() and
	       * explicitly terminate the string.
	       */
	      memcpy(ep, vptr, vlen+1);
	      ep += vlen;
	      *ep = '\0';
	    } else {
	      plog(XLOG_ERROR, EXPAND_ERROR, opt);
	      goto out;
	    }
	  }
	  /*
	   * Done with this variable
	   */
	  break;
	}
      }

      /*
       * Check that the search was successful
       */
      if (!op->name) {
	/*
	 * If it wasn't then scan the
	 * environment for that name
	 * and use any value found
	 */
	char *env = getenv(nbuf);

	if (env) {
	  int vlen = strlen(env);

	  if (BUFSPACE(ep, vlen+1)) {
	    xstrlcpy(ep, env, vlen+1);
	    ep += vlen;
	  } else {
	    plog(XLOG_ERROR, EXPAND_ERROR, opt);
	    goto out;
	  }
	  if (amuDebug(D_STR))
	    plog(XLOG_DEBUG, "Environment gave \"%s\" -> \"%s\"", nbuf, env);
	} else {
	  plog(XLOG_USER, "Unknown sequence \"${%s}\"", nbuf);
	}
      }
    } else {
      /*
       * Error, error
       */
      plog(XLOG_USER, "Unknown $ sequence in \"%s\"", opt);
    }
  }

out:
  /*
   * Handle common case - no expansion
   */
  if (cp == opt) {
    opt = xstrdup(cp);
  } else {
    /*
     * Finish off the expansion
     */
    int vlen = strlen(cp);
    if (BUFSPACE(ep, vlen+1)) {
      xstrlcpy(ep, cp, vlen+1);
      /* ep += vlen; */
    } else {
      plog(XLOG_ERROR, EXPAND_ERROR, opt);
    }

    /*
     * Save the expansion
     */
    opt = xstrdup(expbuf);
  }

  normalize_slash(opt);

  if (amuDebug(D_STR)) {
    plog(XLOG_DEBUG, "Expansion of \"%s\"...", cp_orig);
    plog(XLOG_DEBUG, "......... is \"%s\"", opt);
  }
  return opt;
}