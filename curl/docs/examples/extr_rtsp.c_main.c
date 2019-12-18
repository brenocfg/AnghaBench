#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* version; } ;
typedef  TYPE_1__ curl_version_info_data ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_HEADERDATA ; 
 int /*<<< orphan*/  CURLOPT_NOPROGRESS ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLVERSION_NOW ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 char* VERSION_STR ; 
 int /*<<< orphan*/  _getch () ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 TYPE_1__* curl_version_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_media_control_attribute (char*,char*) ; 
 int /*<<< orphan*/  get_sdp_filename (char const*,char*,scalar_t__) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  my_curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rtsp_describe (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  rtsp_options (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rtsp_play (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  rtsp_setup (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  rtsp_teardown (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char const* stdout ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char* const,char) ; 

int main(int argc, char * const argv[])
{
#if 1
  const char *transport = "RTP/AVP;unicast;client_port=1234-1235";  /* UDP */
#else
  /* TCP */
  const char *transport = "RTP/AVP/TCP;unicast;client_port=1234-1235";
#endif
  const char *range = "0.000-";
  int rc = EXIT_SUCCESS;
  char *base_name = NULL;

  printf("\nRTSP request %s\n", VERSION_STR);
  printf("    Project web site: "
    "https://github.com/BackupGGCode/rtsprequest\n");
  printf("    Requires curl V7.20 or greater\n\n");

  /* check command line */
  if((argc != 2) && (argc != 3)) {
    base_name = strrchr(argv[0], '/');
    if(base_name == NULL) {
      base_name = strrchr(argv[0], '\\');
    }
    if(base_name == NULL) {
      base_name = argv[0];
    }
    else {
      base_name++;
    }
    printf("Usage:   %s url [transport]\n", base_name);
    printf("         url of video server\n");
    printf("         transport (optional) specifier for media stream"
           " protocol\n");
    printf("         default transport: %s\n", transport);
    printf("Example: %s rtsp://192.168.0.2/media/video1\n\n", base_name);
    rc = EXIT_FAILURE;
  }
  else {
    const char *url = argv[1];
    char *uri = malloc(strlen(url) + 32);
    char *sdp_filename = malloc(strlen(url) + 32);
    char *control = malloc(strlen(url) + 32);
    CURLcode res;
    get_sdp_filename(url, sdp_filename, strlen(url) + 32);
    if(argc == 3) {
      transport = argv[2];
    }

    /* initialize curl */
    res = curl_global_init(CURL_GLOBAL_ALL);
    if(res == CURLE_OK) {
      curl_version_info_data *data = curl_version_info(CURLVERSION_NOW);
      CURL *curl;
      fprintf(stderr, "    curl V%s loaded\n", data->version);

      /* initialize this curl session */
      curl = curl_easy_init();
      if(curl != NULL) {
        my_curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        my_curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        my_curl_easy_setopt(curl, CURLOPT_HEADERDATA, stdout);
        my_curl_easy_setopt(curl, CURLOPT_URL, url);

        /* request server options */
        snprintf(uri, strlen(url) + 32, "%s", url);
        rtsp_options(curl, uri);

        /* request session description and write response to sdp file */
        rtsp_describe(curl, uri, sdp_filename);

        /* get media control attribute from sdp file */
        get_media_control_attribute(sdp_filename, control);

        /* setup media stream */
        snprintf(uri, strlen(url) + 32, "%s/%s", url, control);
        rtsp_setup(curl, uri, transport);

        /* start playing media stream */
        snprintf(uri, strlen(url) + 32, "%s/", url);
        rtsp_play(curl, uri, range);
        printf("Playing video, press any key to stop ...");
        _getch();
        printf("\n");

        /* teardown session */
        rtsp_teardown(curl, uri);

        /* cleanup */
        curl_easy_cleanup(curl);
        curl = NULL;
      }
      else {
        fprintf(stderr, "curl_easy_init() failed\n");
      }
      curl_global_cleanup();
    }
    else {
      fprintf(stderr, "curl_global_init(%s) failed: %d\n",
              "CURL_GLOBAL_ALL", res);
    }
    free(control);
    free(sdp_filename);
    free(uri);
  }

  return rc;
}