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
typedef  char gchar ;
typedef  char FILE ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (char*) ; 
 char* fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int j ; 
 int /*<<< orphan*/  lock ; 
 int num_urls ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/ * urls ; 
 char* write_file ; 

void *pull_one_url(void *NaN)
{
  /* Stop threads from entering unless j is incremented */
  pthread_mutex_lock(&lock);
  while(j < num_urls) {
    CURL *curl;
    gchar *http;

    printf("j = %d\n", j);

    http =
      g_strdup_printf("xoap.weather.com/weather/local/%s?cc=*&dayf=5&unit=i\n",
                      urls[j]);

    printf("http %s", http);

    curl = curl_easy_init();
    if(curl) {

      FILE *outfile = fopen(urls[j], "wb");

      /* Set the URL and transfer type */
      curl_easy_setopt(curl, CURLOPT_URL, http);

      /* Write to the file */
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_file);

      j++;  /* critical line */
      pthread_mutex_unlock(&lock);

      curl_easy_perform(curl);

      fclose(outfile);
      printf("fclose\n");

      curl_easy_cleanup(curl);
    }
    g_free(http);

    /* Adds more latency, testing the mutex.*/
    sleep(1);

  } /* end while */
  return NULL;
}