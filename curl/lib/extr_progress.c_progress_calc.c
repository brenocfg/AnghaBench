#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int timediff_t ;
struct curltime {scalar_t__ tv_sec; } ;
struct connectdata {struct Curl_easy* data; } ;
struct TYPE_2__ {int downloaded; int uploaded; int dlspeed; int ulspeed; scalar_t__ lastshow; int speeder_c; int* speeder; int current_speed; struct curltime* speeder_time; scalar_t__ timespent; int /*<<< orphan*/  start; } ;
struct Curl_easy {TYPE_1__ progress; } ;
typedef  int curl_off_t ;

/* Variables and functions */
 int CURL_OFF_T_C (int) ; 
 int CURL_OFF_T_MAX ; 
 int CURR_TIME ; 
 int Curl_timediff (struct curltime,struct curltime) ; 
 scalar_t__ Curl_timediff_us (struct curltime,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static bool progress_calc(struct connectdata *conn, struct curltime now)
{
  curl_off_t timespent;
  curl_off_t timespent_ms; /* milliseconds */
  struct Curl_easy *data = conn->data;
  curl_off_t dl = data->progress.downloaded;
  curl_off_t ul = data->progress.uploaded;
  bool timetoshow = FALSE;

  /* The time spent so far (from the start) */
  data->progress.timespent = Curl_timediff_us(now, data->progress.start);
  timespent = (curl_off_t)data->progress.timespent/1000000; /* seconds */
  timespent_ms = (curl_off_t)data->progress.timespent/1000; /* ms */

  /* The average download speed this far */
  if(dl < CURL_OFF_T_MAX/1000)
    data->progress.dlspeed = (dl * 1000 / (timespent_ms>0?timespent_ms:1));
  else
    data->progress.dlspeed = (dl / (timespent>0?timespent:1));

  /* The average upload speed this far */
  if(ul < CURL_OFF_T_MAX/1000)
    data->progress.ulspeed = (ul * 1000 / (timespent_ms>0?timespent_ms:1));
  else
    data->progress.ulspeed = (ul / (timespent>0?timespent:1));

  /* Calculations done at most once a second, unless end is reached */
  if(data->progress.lastshow != now.tv_sec) {
    int countindex; /* amount of seconds stored in the speeder array */
    int nowindex = data->progress.speeder_c% CURR_TIME;
    data->progress.lastshow = now.tv_sec;
    timetoshow = TRUE;

    /* Let's do the "current speed" thing, with the dl + ul speeds
       combined. Store the speed at entry 'nowindex'. */
    data->progress.speeder[ nowindex ] =
      data->progress.downloaded + data->progress.uploaded;

    /* remember the exact time for this moment */
    data->progress.speeder_time [ nowindex ] = now;

    /* advance our speeder_c counter, which is increased every time we get
       here and we expect it to never wrap as 2^32 is a lot of seconds! */
    data->progress.speeder_c++;

    /* figure out how many index entries of data we have stored in our speeder
       array. With N_ENTRIES filled in, we have about N_ENTRIES-1 seconds of
       transfer. Imagine, after one second we have filled in two entries,
       after two seconds we've filled in three entries etc. */
    countindex = ((data->progress.speeder_c >= CURR_TIME)?
                  CURR_TIME:data->progress.speeder_c) - 1;

    /* first of all, we don't do this if there's no counted seconds yet */
    if(countindex) {
      int checkindex;
      timediff_t span_ms;

      /* Get the index position to compare with the 'nowindex' position.
         Get the oldest entry possible. While we have less than CURR_TIME
         entries, the first entry will remain the oldest. */
      checkindex = (data->progress.speeder_c >= CURR_TIME)?
        data->progress.speeder_c%CURR_TIME:0;

      /* Figure out the exact time for the time span */
      span_ms = Curl_timediff(now, data->progress.speeder_time[checkindex]);
      if(0 == span_ms)
        span_ms = 1; /* at least one millisecond MUST have passed */

      /* Calculate the average speed the last 'span_ms' milliseconds */
      {
        curl_off_t amount = data->progress.speeder[nowindex]-
          data->progress.speeder[checkindex];

        if(amount > CURL_OFF_T_C(4294967) /* 0xffffffff/1000 */)
          /* the 'amount' value is bigger than would fit in 32 bits if
             multiplied with 1000, so we use the double math for this */
          data->progress.current_speed = (curl_off_t)
            ((double)amount/((double)span_ms/1000.0));
        else
          /* the 'amount' value is small enough to fit within 32 bits even
             when multiplied with 1000 */
          data->progress.current_speed = amount*CURL_OFF_T_C(1000)/span_ms;
      }
    }
    else
      /* the first second we use the average */
      data->progress.current_speed =
        data->progress.ulspeed + data->progress.dlspeed;

  } /* Calculations end */
  return timetoshow;
}