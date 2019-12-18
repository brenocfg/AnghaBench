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
typedef  int /*<<< orphan*/ * FT_Service_PfrMetrics ;
typedef  scalar_t__ FT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_FACE_LOOKUP_SERVICE (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFR_METRICS ; 

__attribute__((used)) static FT_Service_PfrMetrics
  ft_pfr_check( FT_Face  face )
  {
    FT_Service_PfrMetrics  service = NULL;


    if ( face )
      FT_FACE_LOOKUP_SERVICE( face, service, PFR_METRICS );

    return service;
  }