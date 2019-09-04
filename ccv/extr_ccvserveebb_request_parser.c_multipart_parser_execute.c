#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int multipart_state; size_t multipart_index; char* multipart_lookbehind; } ;
typedef  TYPE_1__ ebb_request_parser ;
struct TYPE_7__ {char* multipart_boundary; int /*<<< orphan*/  (* on_part_data_complete ) (TYPE_2__*) ;int /*<<< orphan*/  multipart_boundary_len; int /*<<< orphan*/  number_of_multipart_headers; int /*<<< orphan*/  (* on_multipart_headers_complete ) (TYPE_2__*) ;} ;

/* Variables and functions */
 char CR ; 
 TYPE_2__* CURRENT ; 
 int /*<<< orphan*/  EMIT_DATA_CB (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  EMIT_HEADER_CB (int /*<<< orphan*/ ,char const*,size_t) ; 
 char LF ; 
 int /*<<< orphan*/  multipart_header_field ; 
 int /*<<< orphan*/  multipart_header_value ; 
 int /*<<< orphan*/  part_data ; 
#define  s_end 143 
#define  s_header_field 142 
#define  s_header_field_start 141 
#define  s_header_value 140 
#define  s_header_value_almost_done 139 
#define  s_header_value_start 138 
#define  s_headers_almost_done 137 
#define  s_part_data 136 
#define  s_part_data_almost_boundary 135 
#define  s_part_data_almost_end 134 
#define  s_part_data_boundary 133 
#define  s_part_data_end 132 
#define  s_part_data_final_hyphen 131 
#define  s_part_data_start 130 
#define  s_start 129 
#define  s_start_boundary 128 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 char tolower (char) ; 

size_t multipart_parser_execute(ebb_request_parser* parser, const char *buf, size_t len)
{
  size_t i = 0;
  size_t mark = 0;
  char c, cl;
  int is_last = 0;

  while(!is_last) {
    c = buf[i];
    is_last = (i == (len - 1));
    switch (parser->multipart_state) {
      case s_start:
		CURRENT->number_of_multipart_headers = 0;
        parser->multipart_index = 0;
        parser->multipart_state = s_start_boundary;

      /* fallthrough */
      case s_start_boundary:
	    // every time needs to take into account the first two '-'
        if (parser->multipart_index == CURRENT->multipart_boundary_len + 2) {
          if (c != CR) {
            return i;
          }
          parser->multipart_index++;
          break;
        } else if (parser->multipart_index == (CURRENT->multipart_boundary_len + 3)) {
          if (c != LF) {
            return i;
          }
		  CURRENT->number_of_multipart_headers = 0;
          parser->multipart_index = 0;
          parser->multipart_state = s_header_field_start;
          break;
        }
        if (c != CURRENT->multipart_boundary[parser->multipart_index]) {
          return i;
        }
        parser->multipart_index++;
        break;

      case s_header_field_start:
        mark = i;
        parser->multipart_state = s_header_field;

      /* fallthrough */
      case s_header_field:
        if (c == CR) {
          parser->multipart_state = s_headers_almost_done;
          break;
        }

        if (c == '-') {
          break;
        }

        if (c == ':') {
          EMIT_HEADER_CB(multipart_header_field, buf + mark, i - mark);
          parser->multipart_state = s_header_value_start;
          break;
        }

        cl = tolower(c);
        if (cl < 'a' || cl > 'z') {
          return i;
        }
        if (is_last)
          EMIT_HEADER_CB(multipart_header_field, buf + mark, (i - mark) + 1);
        break;

      case s_headers_almost_done:
        if (c != LF) {
          return i;
        }

        parser->multipart_state = s_part_data_start;
        break;

      case s_header_value_start:
        if (c == ' ') {
          break;
        }

        mark = i;
        parser->multipart_state = s_header_value;

      /* fallthrough */
      case s_header_value:
        if (c == CR) {
          EMIT_HEADER_CB(multipart_header_value, buf + mark, i - mark);
          parser->multipart_state = s_header_value_almost_done;
        }
        if (is_last)
          EMIT_HEADER_CB(multipart_header_value, buf + mark, (i - mark) + 1);
        break;

      case s_header_value_almost_done:
        if (c != LF) {
          return i;
        }
		CURRENT->number_of_multipart_headers++;
        parser->multipart_state = s_header_field_start;
        break;

      case s_part_data_start:
        if (CURRENT->on_multipart_headers_complete)
		  CURRENT->on_multipart_headers_complete(CURRENT);
        mark = i;
        parser->multipart_state = s_part_data;

      /* fallthrough */
      case s_part_data:
        if (c == CR) {
          EMIT_DATA_CB(part_data, buf + mark, i - mark);
          mark = i;
          parser->multipart_state = s_part_data_almost_boundary;
          parser->multipart_lookbehind[0] = CR;
          break;
        }
        if (is_last)
          EMIT_DATA_CB(part_data, buf + mark, (i - mark) + 1);
        break;

      case s_part_data_almost_boundary:
        if (c == LF) {
          parser->multipart_state = s_part_data_boundary;
          parser->multipart_lookbehind[1] = LF;
		  CURRENT->number_of_multipart_headers = 0;
          parser->multipart_index = 0;
          break;
        }
        EMIT_DATA_CB(part_data, parser->multipart_lookbehind, 1);
        parser->multipart_state = s_part_data;
        mark = i --;
        break;

      case s_part_data_boundary:
        if (CURRENT->multipart_boundary[parser->multipart_index] != c) {
          EMIT_DATA_CB(part_data, parser->multipart_lookbehind, 2 + parser->multipart_index);
          parser->multipart_state = s_part_data;
          mark = i --;
          break;
        }
        parser->multipart_lookbehind[2 + parser->multipart_index] = c;
        if ((++ parser->multipart_index) == CURRENT->multipart_boundary_len + 2) {
          if (CURRENT->on_part_data_complete)
		    CURRENT->on_part_data_complete(CURRENT);
          parser->multipart_state = s_part_data_almost_end;
        }
        break;

      case s_part_data_almost_end:
        if (c == '-') {
          parser->multipart_state = s_part_data_final_hyphen;
          break;
        }
        if (c == CR) {
          parser->multipart_state = s_part_data_end;
          break;
        }
        return i;
   
      case s_part_data_final_hyphen:
        if (c == '-') {
          parser->multipart_state = s_end;
          break;
        }
        return i;

      case s_part_data_end:
        if (c == LF) {
          parser->multipart_state = s_header_field_start;
          break;
        }
        return i;

      case s_end:
        break;

      default:
        return 0;
    }
    ++i;
  }

  return len;
}