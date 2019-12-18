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

/* Variables and functions */
 int /*<<< orphan*/  CountLightmaps () ; 
 int /*<<< orphan*/  CreateFilters () ; 
 int /*<<< orphan*/  CreateSurfaceLights () ; 
 int /*<<< orphan*/  DefaultExtension (double,char*) ; 
 int /*<<< orphan*/  ExpandArg (char*) ; 
 int /*<<< orphan*/  FindSkyBrushes () ; 
 double I_FloatTime () ; 
 int /*<<< orphan*/  InitPakFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitTrace () ; 
 int /*<<< orphan*/  LightWorld () ; 
 int /*<<< orphan*/  LoadBSPFile (double) ; 
 int /*<<< orphan*/  LoadShaderInfo () ; 
 int /*<<< orphan*/  ParseEntities () ; 
 int /*<<< orphan*/  SetEntityOrigins () ; 
 int /*<<< orphan*/  SetQdirFromPath (char*) ; 
 int /*<<< orphan*/  StripExtension (double) ; 
 int /*<<< orphan*/  ThreadSetDefault () ; 
 char* ValueForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  WriteBSPFile (double) ; 
 int /*<<< orphan*/  _printf (char*,...) ; 
 double areaScale ; 
 double atof (char*) ; 
 void* atoi (char*) ; 
 void* dump ; 
 int /*<<< orphan*/ * entities ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 void* extra ; 
 void* extraWide ; 
 int /*<<< orphan*/  gamedir ; 
 int /*<<< orphan*/ * gridSize ; 
 void* lightmapBorder ; 
 void* noSurfaces ; 
 void* nogridlighting ; 
 void* notrace ; 
 void* novertexlighting ; 
 void* numthreads ; 
 void* patchshadows ; 
 double pointScale ; 
 void* qfalse ; 
 void* qtrue ; 
 int samplesize ; 
 double source ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (double,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 void* verbose ; 

int LightMain (int argc, char **argv) {
	int			i;
	double		start, end;
	const char	*value;

	_printf ("----- Lighting ----\n");

	verbose = qfalse;

	for (i=1 ; i<argc ; i++) {
		if (!strcmp(argv[i],"-tempname"))
    {
      i++;
    } else if (!strcmp(argv[i],"-v")) {
			verbose = qtrue;
		} else if (!strcmp(argv[i],"-threads")) {
			numthreads = atoi (argv[i+1]);
			i++;
		} else if (!strcmp(argv[i],"-area")) {
			areaScale *= atof(argv[i+1]);
			_printf ("area light scaling at %f\n", areaScale);
			i++;
		} else if (!strcmp(argv[i],"-point")) {
			pointScale *= atof(argv[i+1]);
			_printf ("point light scaling at %f\n", pointScale);
			i++;
		} else if (!strcmp(argv[i],"-notrace")) {
			notrace = qtrue;
			_printf ("No occlusion tracing\n");
		} else if (!strcmp(argv[i],"-patchshadows")) {
			patchshadows = qtrue;
			_printf ("Patch shadow casting enabled\n");
		} else if (!strcmp(argv[i],"-extra")) {
			extra = qtrue;
			_printf ("Extra detail tracing\n");
		} else if (!strcmp(argv[i],"-extrawide")) {
			extra = qtrue;
			extraWide = qtrue;
			_printf ("Extra wide detail tracing\n");
		} else if (!strcmp(argv[i], "-samplesize")) {
			samplesize = atoi(argv[i+1]);
			if (samplesize < 1) samplesize = 1;
			i++;
			_printf("lightmap sample size is %dx%d units\n", samplesize, samplesize);
		} else if (!strcmp(argv[i], "-novertex")) {
			novertexlighting = qtrue;
			_printf("no vertex lighting = true\n");
		} else if (!strcmp(argv[i], "-nogrid")) {
			nogridlighting = qtrue;
			_printf("no grid lighting = true\n");
		} else if (!strcmp(argv[i],"-border")) {
			lightmapBorder = qtrue;
			_printf ("Adding debug border to lightmaps\n");
		} else if (!strcmp(argv[i],"-nosurf")) {
			noSurfaces = qtrue;
			_printf ("Not tracing against surfaces\n" );
		} else if (!strcmp(argv[i],"-dump")) {
			dump = qtrue;
			_printf ("Dumping occlusion maps\n");
		} else {
			break;
		}
	}

	ThreadSetDefault ();

	if (i != argc - 1) {
		_printf("usage: q3map -light [-<switch> [-<switch> ...]] <mapname>\n"
				"\n"
				"Switches:\n"
				"   v              = verbose output\n"
				"   threads <X>    = set number of threads to X\n"
				"   area <V>       = set the area light scale to V\n"
				"   point <W>      = set the point light scale to W\n"
				"   notrace        = don't cast any shadows\n"
				"   extra          = enable super sampling for anti-aliasing\n"
				"   extrawide      = same as extra but smoothen more\n"
				"   nogrid         = don't calculate light grid for dynamic model lighting\n"
				"   novertex       = don't calculate vertex lighting\n"
				"   samplesize <N> = set the lightmap pixel size to NxN units\n");
		exit(0);
	}

	start = I_FloatTime ();

	SetQdirFromPath (argv[i]);	

#ifdef _WIN32
	InitPakFile(gamedir, NULL);
#endif

	strcpy (source, ExpandArg(argv[i]));
	StripExtension (source);
	DefaultExtension (source, ".bsp");

	LoadShaderInfo();

	_printf ("reading %s\n", source);

	LoadBSPFile (source);

	FindSkyBrushes();

	ParseEntities();

	value = ValueForKey( &entities[0], "gridsize" );
	if (strlen(value)) {
		sscanf( value, "%f %f %f", &gridSize[0], &gridSize[1], &gridSize[2] );
		_printf("grid size = {%1.1f, %1.1f, %1.1f}\n", gridSize[0], gridSize[1], gridSize[2]);
	}

	CreateFilters();

	InitTrace();

	SetEntityOrigins();

	CountLightmaps();

	CreateSurfaceLights();

	LightWorld();

	_printf ("writing %s\n", source);
	WriteBSPFile (source);

	end = I_FloatTime ();
	_printf ("%5.0f seconds elapsed\n", end-start);
	
	return 0;
}