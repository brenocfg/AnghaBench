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
typedef  int /*<<< orphan*/  WriterContext ;
struct TYPE_2__ {int log_level; int category; int parent_category; scalar_t__ log_message; scalar_t__ parent_name; scalar_t__ context_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_log (int /*<<< orphan*/ ) ; 
 TYPE_1__* log_buffer ; 
 int log_buffer_size ; 
 int /*<<< orphan*/  log_mutex ; 
 int /*<<< orphan*/  print_int (char*,int) ; 
 int /*<<< orphan*/  print_str (char*,scalar_t__) ; 
 int /*<<< orphan*/  print_str_opt (char*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_header (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int show_log(WriterContext *w, int section_ids, int section_id, int log_level)
{
    int i;
    pthread_mutex_lock(&log_mutex);
    if (!log_buffer_size) {
        pthread_mutex_unlock(&log_mutex);
        return 0;
    }
    writer_print_section_header(w, section_ids);

    for (i=0; i<log_buffer_size; i++) {
        if (log_buffer[i].log_level <= log_level) {
            writer_print_section_header(w, section_id);
            print_str("context", log_buffer[i].context_name);
            print_int("level", log_buffer[i].log_level);
            print_int("category", log_buffer[i].category);
            if (log_buffer[i].parent_name) {
                print_str("parent_context", log_buffer[i].parent_name);
                print_int("parent_category", log_buffer[i].parent_category);
            } else {
                print_str_opt("parent_context", "N/A");
                print_str_opt("parent_category", "N/A");
            }
            print_str("message", log_buffer[i].log_message);
            writer_print_section_footer(w);
        }
    }
    clear_log(0);
    pthread_mutex_unlock(&log_mutex);

    writer_print_section_footer(w);

    return 0;
}