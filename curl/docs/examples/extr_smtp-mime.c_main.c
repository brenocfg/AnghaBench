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
typedef  char curl_slist ;
typedef  int /*<<< orphan*/  curl_mimepart ;
typedef  char curl_mime ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 char* CC ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  CURLOPT_MAIL_FROM ; 
 int /*<<< orphan*/  CURLOPT_MAIL_RCPT ; 
 int /*<<< orphan*/  CURLOPT_MIMEPOST ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_ZERO_TERMINATED ; 
 char* FROM ; 
 char* TO ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* curl_easy_strerror (scalar_t__) ; 
 int /*<<< orphan*/ * curl_mime_addpart (char*) ; 
 int /*<<< orphan*/  curl_mime_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_mime_filedata (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_mime_free (char*) ; 
 int /*<<< orphan*/  curl_mime_headers (int /*<<< orphan*/ *,char*,int) ; 
 char* curl_mime_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_mime_subparts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_mime_type (int /*<<< orphan*/ *,char*) ; 
 char* curl_slist_append (char*,char const*) ; 
 int /*<<< orphan*/  curl_slist_free_all (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char** headers_text ; 
 int /*<<< orphan*/  inline_html ; 
 int /*<<< orphan*/  inline_text ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
  CURL *curl;
  CURLcode res = CURLE_OK;

  curl = curl_easy_init();
  if(curl) {
    struct curl_slist *headers = NULL;
    struct curl_slist *recipients = NULL;
    struct curl_slist *slist = NULL;
    curl_mime *mime;
    curl_mime *alt;
    curl_mimepart *part;
    const char **cpp;

    /* This is the URL for your mailserver */
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://mail.example.com");

    /* Note that this option isn't strictly required, omitting it will result
     * in libcurl sending the MAIL FROM command with empty sender data. All
     * autoresponses should have an empty reverse-path, and should be directed
     * to the address in the reverse-path which triggered them. Otherwise,
     * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
     * details.
     */
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);

    /* Add two recipients, in this particular case they correspond to the
     * To: and Cc: addressees in the header, but they could be any kind of
     * recipient. */
    recipients = curl_slist_append(recipients, TO);
    recipients = curl_slist_append(recipients, CC);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    /* Build and set the message header list. */
    for(cpp = headers_text; *cpp; cpp++)
      headers = curl_slist_append(headers, *cpp);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    /* Build the mime message. */
    mime = curl_mime_init(curl);

    /* The inline part is an alternative proposing the html and the text
       versions of the e-mail. */
    alt = curl_mime_init(curl);

    /* HTML message. */
    part = curl_mime_addpart(alt);
    curl_mime_data(part, inline_html, CURL_ZERO_TERMINATED);
    curl_mime_type(part, "text/html");

    /* Text message. */
    part = curl_mime_addpart(alt);
    curl_mime_data(part, inline_text, CURL_ZERO_TERMINATED);

    /* Create the inline part. */
    part = curl_mime_addpart(mime);
    curl_mime_subparts(part, alt);
    curl_mime_type(part, "multipart/alternative");
    slist = curl_slist_append(NULL, "Content-Disposition: inline");
    curl_mime_headers(part, slist, 1);

    /* Add the current source program as an attachment. */
    part = curl_mime_addpart(mime);
    curl_mime_filedata(part, "smtp-mime.c");
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

    /* Send the message */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Free lists. */
    curl_slist_free_all(recipients);
    curl_slist_free_all(headers);

    /* curl won't send the QUIT command until you call cleanup, so you should
     * be able to re-use this connection for additional messages (setting
     * CURLOPT_MAIL_FROM and CURLOPT_MAIL_RCPT as required, and calling
     * curl_easy_perform() again. It may not be a good idea to keep the
     * connection open for a very long time though (more than a few minutes
     * may result in the server timing out the connection), and you do want to
     * clean up in the end.
     */
    curl_easy_cleanup(curl);

    /* Free multipart message. */
    curl_mime_free(mime);
  }

  return (int)res;
}