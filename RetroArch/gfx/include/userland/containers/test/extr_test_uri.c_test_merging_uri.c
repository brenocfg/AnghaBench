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
typedef  int /*<<< orphan*/  VC_URI_PARTS_T ;
struct TYPE_3__ {int /*<<< orphan*/  merged; int /*<<< orphan*/  relative; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ MERGE_URI_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_INFO (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int check_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vc_uri_create () ; 
 int /*<<< orphan*/  vc_uri_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_merging_uri(VC_URI_PARTS_T *uri, MERGE_URI_T *uri_data)
{
   VC_URI_PARTS_T *base_uri;

   LOG_INFO(NULL, "Base <%s>, relative <%s>, expect <%s>", uri_data->base, uri_data->relative, uri_data->merged);

   vc_uri_clear(uri);
   base_uri = vc_uri_create();
   if (!base_uri)
   {
      LOG_ERROR(NULL, "*** Failed to allocate base URI structure");
      return 1;
   }

   if (!vc_uri_parse(base_uri, uri_data->base))
   {
      LOG_ERROR(NULL, "*** Failed to parse base URI structure");
      return 1;
   }
   if (!vc_uri_parse(uri, uri_data->relative))
   {
      LOG_ERROR(NULL, "*** Failed to parse relative URI structure");
      return 1;
   }

   if (!vc_uri_merge(base_uri, uri))
   {
      LOG_ERROR(NULL, "*** Failed to merge base and relative URIs");
      return 1;
   }

   vc_uri_release(base_uri);

   return check_uri(uri, uri_data->merged);
}