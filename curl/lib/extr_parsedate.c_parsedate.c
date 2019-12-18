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
typedef  int time_t ;
struct my_tm {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; } ;
typedef  enum assume { ____Placeholder_assume } assume ;

/* Variables and functions */
 int DATE_MDAY ; 
 int DATE_YEAR ; 
 int FALSE ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
 scalar_t__ ISALPHA (char const) ; 
 scalar_t__ ISDIGIT (char const) ; 
 int PARSEDATE_FAIL ; 
 int PARSEDATE_LATER ; 
 int PARSEDATE_OK ; 
 int PARSEDATE_SOONER ; 
 int TIME_T_MAX ; 
 int TIME_T_MIN ; 
 int TRUE ; 
 int checkday (char*,size_t) ; 
 int checkmonth (char*) ; 
 int checktz (char*) ; 
 int curlx_sltosi (long) ; 
 int errno ; 
 int /*<<< orphan*/  my_timegm (struct my_tm*,int*) ; 
 int /*<<< orphan*/  skip (char const**) ; 
 int sscanf (char const*,char*,...) ; 
 size_t strlen (char*) ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static int parsedate(const char *date, time_t *output)
{
  time_t t = 0;
  int wdaynum = -1;  /* day of the week number, 0-6 (mon-sun) */
  int monnum = -1;   /* month of the year number, 0-11 */
  int mdaynum = -1; /* day of month, 1 - 31 */
  int hournum = -1;
  int minnum = -1;
  int secnum = -1;
  int yearnum = -1;
  int tzoff = -1;
  struct my_tm tm;
  enum assume dignext = DATE_MDAY;
  const char *indate = date; /* save the original pointer */
  int part = 0; /* max 6 parts */

  while(*date && (part < 6)) {
    bool found = FALSE;

    skip(&date);

    if(ISALPHA(*date)) {
      /* a name coming up */
      char buf[32]="";
      size_t len;
      if(sscanf(date, "%31[ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                          "abcdefghijklmnopqrstuvwxyz]", buf))
        len = strlen(buf);
      else
        len = 0;

      if(wdaynum == -1) {
        wdaynum = checkday(buf, len);
        if(wdaynum != -1)
          found = TRUE;
      }
      if(!found && (monnum == -1)) {
        monnum = checkmonth(buf);
        if(monnum != -1)
          found = TRUE;
      }

      if(!found && (tzoff == -1)) {
        /* this just must be a time zone string */
        tzoff = checktz(buf);
        if(tzoff != -1)
          found = TRUE;
      }

      if(!found)
        return PARSEDATE_FAIL; /* bad string */

      date += len;
    }
    else if(ISDIGIT(*date)) {
      /* a digit */
      int val;
      char *end;
      int len = 0;
      if((secnum == -1) &&
         (3 == sscanf(date, "%02d:%02d:%02d%n",
                      &hournum, &minnum, &secnum, &len))) {
        /* time stamp! */
        date += len;
      }
      else if((secnum == -1) &&
              (2 == sscanf(date, "%02d:%02d%n", &hournum, &minnum, &len))) {
        /* time stamp without seconds */
        date += len;
        secnum = 0;
      }
      else {
        long lval;
        int error;
        int old_errno;

        old_errno = errno;
        errno = 0;
        lval = strtol(date, &end, 10);
        error = errno;
        if(errno != old_errno)
          errno = old_errno;

        if(error)
          return PARSEDATE_FAIL;

#if LONG_MAX != INT_MAX
        if((lval > (long)INT_MAX) || (lval < (long)INT_MIN))
          return PARSEDATE_FAIL;
#endif

        val = curlx_sltosi(lval);

        if((tzoff == -1) &&
           ((end - date) == 4) &&
           (val <= 1400) &&
           (indate< date) &&
           ((date[-1] == '+' || date[-1] == '-'))) {
          /* four digits and a value less than or equal to 1400 (to take into
             account all sorts of funny time zone diffs) and it is preceded
             with a plus or minus. This is a time zone indication.  1400 is
             picked since +1300 is frequently used and +1400 is mentioned as
             an edge number in the document "ISO C 200X Proposal: Timezone
             Functions" at http://david.tribble.com/text/c0xtimezone.html If
             anyone has a more authoritative source for the exact maximum time
             zone offsets, please speak up! */
          found = TRUE;
          tzoff = (val/100 * 60 + val%100)*60;

          /* the + and - prefix indicates the local time compared to GMT,
             this we need their reversed math to get what we want */
          tzoff = date[-1]=='+'?-tzoff:tzoff;
        }

        if(((end - date) == 8) &&
           (yearnum == -1) &&
           (monnum == -1) &&
           (mdaynum == -1)) {
          /* 8 digits, no year, month or day yet. This is YYYYMMDD */
          found = TRUE;
          yearnum = val/10000;
          monnum = (val%10000)/100-1; /* month is 0 - 11 */
          mdaynum = val%100;
        }

        if(!found && (dignext == DATE_MDAY) && (mdaynum == -1)) {
          if((val > 0) && (val<32)) {
            mdaynum = val;
            found = TRUE;
          }
          dignext = DATE_YEAR;
        }

        if(!found && (dignext == DATE_YEAR) && (yearnum == -1)) {
          yearnum = val;
          found = TRUE;
          if(yearnum < 100) {
            if(yearnum > 70)
              yearnum += 1900;
            else
              yearnum += 2000;
          }
          if(mdaynum == -1)
            dignext = DATE_MDAY;
        }

        if(!found)
          return PARSEDATE_FAIL;

        date = end;
      }
    }

    part++;
  }

  if(-1 == secnum)
    secnum = minnum = hournum = 0; /* no time, make it zero */

  if((-1 == mdaynum) ||
     (-1 == monnum) ||
     (-1 == yearnum))
    /* lacks vital info, fail */
    return PARSEDATE_FAIL;

#ifdef HAVE_TIME_T_UNSIGNED
  if(yearnum < 1970) {
    /* only positive numbers cannot return earlier */
    *output = TIME_T_MIN;
    return PARSEDATE_SOONER;
  }
#endif

#if (SIZEOF_TIME_T < 5)

#ifdef HAVE_TIME_T_UNSIGNED
  /* an unsigned 32 bit time_t can only hold dates to 2106 */
  if(yearnum > 2105) {
    *output = TIME_T_MAX;
    return PARSEDATE_LATER;
  }
#else
  /* a signed 32 bit time_t can only hold dates to the beginning of 2038 */
  if(yearnum > 2037) {
    *output = TIME_T_MAX;
    return PARSEDATE_LATER;
  }
  if(yearnum < 1903) {
    *output = TIME_T_MIN;
    return PARSEDATE_SOONER;
  }
#endif

#else
  /* The Gregorian calendar was introduced 1582 */
  if(yearnum < 1583)
    return PARSEDATE_FAIL;
#endif

  if((mdaynum > 31) || (monnum > 11) ||
     (hournum > 23) || (minnum > 59) || (secnum > 60))
    return PARSEDATE_FAIL; /* clearly an illegal date */

  tm.tm_sec = secnum;
  tm.tm_min = minnum;
  tm.tm_hour = hournum;
  tm.tm_mday = mdaynum;
  tm.tm_mon = monnum;
  tm.tm_year = yearnum;

  /* my_timegm() returns a time_t. time_t is often 32 bits, sometimes even on
     architectures that feature 64 bit 'long' but ultimately time_t is the
     correct data type to use.
  */
  my_timegm(&tm, &t);

  /* Add the time zone diff between local time zone and GMT. */
  if(tzoff == -1)
    tzoff = 0;

  if((tzoff > 0) && (t > TIME_T_MAX - tzoff)) {
    *output = TIME_T_MAX;
    return PARSEDATE_LATER; /* time_t overflow */
  }

  t += tzoff;

  *output = t;

  return PARSEDATE_OK;
}