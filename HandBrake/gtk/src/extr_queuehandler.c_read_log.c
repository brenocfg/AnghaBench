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
struct TYPE_3__ {char* extra_activity_path; int /*<<< orphan*/  extra_activity_buffer; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkTextIter ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t ACTIVITY_MAX_READ_SZ ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_fopen (char const*,char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_malloc (size_t) ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/  gtk_text_buffer_get_end_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_text_buffer_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  gtk_text_buffer_set_text (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static void read_log(signal_user_data_t * ud, const char * log_path)
{
    FILE        * f;
    size_t        size, req_size;
    GtkTextIter   iter;
    char        * buf;

    if (ud->extra_activity_path != NULL &&
        !strcmp(ud->extra_activity_path, log_path))
    {
        return;
    }
    g_free(ud->extra_activity_path);
    ud->extra_activity_path = g_strdup(log_path);

    gtk_text_buffer_set_text(ud->extra_activity_buffer, "", 0);

    f = g_fopen(log_path, "r");
    if (f == NULL)
    {
        return;
    }
    fseek(f, 0, SEEK_END);
    req_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (req_size > ACTIVITY_MAX_READ_SZ)
    {
        req_size = ACTIVITY_MAX_READ_SZ;
    }
    buf = g_malloc(req_size);
    while (!feof(f))
    {
        size = fread(buf, 1, req_size, f);
        if (size <= 0)
        {
            break;
        }
        gtk_text_buffer_get_end_iter(ud->extra_activity_buffer, &iter);
        gtk_text_buffer_insert(ud->extra_activity_buffer, &iter, buf, size);
    }
    fclose(f);
    g_free(buf);
}