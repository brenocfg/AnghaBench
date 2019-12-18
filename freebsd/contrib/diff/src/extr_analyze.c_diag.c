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
struct partition {int xmid; int ymid; int lo_minimal; int hi_minimal; } ;
typedef  int lin ;

/* Variables and functions */
 int LIN_MAX ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int SNAKE_LIMIT ; 
 int* bdiag ; 
 int* fdiag ; 
 scalar_t__ speed_large_files ; 
 int too_expensive ; 
 int* xvec ; 
 int* yvec ; 

__attribute__((used)) static void
diag (lin xoff, lin xlim, lin yoff, lin ylim, bool find_minimal,
      struct partition *part)
{
  lin *const fd = fdiag;	/* Give the compiler a chance. */
  lin *const bd = bdiag;	/* Additional help for the compiler. */
  lin const *const xv = xvec;	/* Still more help for the compiler. */
  lin const *const yv = yvec;	/* And more and more . . . */
  lin const dmin = xoff - ylim;	/* Minimum valid diagonal. */
  lin const dmax = xlim - yoff;	/* Maximum valid diagonal. */
  lin const fmid = xoff - yoff;	/* Center diagonal of top-down search. */
  lin const bmid = xlim - ylim;	/* Center diagonal of bottom-up search. */
  lin fmin = fmid, fmax = fmid;	/* Limits of top-down search. */
  lin bmin = bmid, bmax = bmid;	/* Limits of bottom-up search. */
  lin c;			/* Cost. */
  bool odd = (fmid - bmid) & 1;	/* True if southeast corner is on an odd
				   diagonal with respect to the northwest. */

  fd[fmid] = xoff;
  bd[bmid] = xlim;

  for (c = 1;; ++c)
    {
      lin d;			/* Active diagonal. */
      bool big_snake = false;

      /* Extend the top-down search by an edit step in each diagonal. */
      fmin > dmin ? fd[--fmin - 1] = -1 : ++fmin;
      fmax < dmax ? fd[++fmax + 1] = -1 : --fmax;
      for (d = fmax; d >= fmin; d -= 2)
	{
	  lin x, y, oldx, tlo = fd[d - 1], thi = fd[d + 1];

	  if (tlo >= thi)
	    x = tlo + 1;
	  else
	    x = thi;
	  oldx = x;
	  y = x - d;
	  while (x < xlim && y < ylim && xv[x] == yv[y])
	    ++x, ++y;
	  if (x - oldx > SNAKE_LIMIT)
	    big_snake = true;
	  fd[d] = x;
	  if (odd && bmin <= d && d <= bmax && bd[d] <= x)
	    {
	      part->xmid = x;
	      part->ymid = y;
	      part->lo_minimal = part->hi_minimal = true;
	      return;
	    }
	}

      /* Similarly extend the bottom-up search.  */
      bmin > dmin ? bd[--bmin - 1] = LIN_MAX : ++bmin;
      bmax < dmax ? bd[++bmax + 1] = LIN_MAX : --bmax;
      for (d = bmax; d >= bmin; d -= 2)
	{
	  lin x, y, oldx, tlo = bd[d - 1], thi = bd[d + 1];

	  if (tlo < thi)
	    x = tlo;
	  else
	    x = thi - 1;
	  oldx = x;
	  y = x - d;
	  while (x > xoff && y > yoff && xv[x - 1] == yv[y - 1])
	    --x, --y;
	  if (oldx - x > SNAKE_LIMIT)
	    big_snake = true;
	  bd[d] = x;
	  if (!odd && fmin <= d && d <= fmax && x <= fd[d])
	    {
	      part->xmid = x;
	      part->ymid = y;
	      part->lo_minimal = part->hi_minimal = true;
	      return;
	    }
	}

      if (find_minimal)
	continue;

      /* Heuristic: check occasionally for a diagonal that has made
	 lots of progress compared with the edit distance.
	 If we have any such, find the one that has made the most
	 progress and return it as if it had succeeded.

	 With this heuristic, for files with a constant small density
	 of changes, the algorithm is linear in the file size.  */

      if (200 < c && big_snake && speed_large_files)
	{
	  lin best = 0;

	  for (d = fmax; d >= fmin; d -= 2)
	    {
	      lin dd = d - fmid;
	      lin x = fd[d];
	      lin y = x - d;
	      lin v = (x - xoff) * 2 - dd;
	      if (v > 12 * (c + (dd < 0 ? -dd : dd)))
		{
		  if (v > best
		      && xoff + SNAKE_LIMIT <= x && x < xlim
		      && yoff + SNAKE_LIMIT <= y && y < ylim)
		    {
		      /* We have a good enough best diagonal;
			 now insist that it end with a significant snake.  */
		      int k;

		      for (k = 1; xv[x - k] == yv[y - k]; k++)
			if (k == SNAKE_LIMIT)
			  {
			    best = v;
			    part->xmid = x;
			    part->ymid = y;
			    break;
			  }
		    }
		}
	    }
	  if (best > 0)
	    {
	      part->lo_minimal = true;
	      part->hi_minimal = false;
	      return;
	    }

	  best = 0;
	  for (d = bmax; d >= bmin; d -= 2)
	    {
	      lin dd = d - bmid;
	      lin x = bd[d];
	      lin y = x - d;
	      lin v = (xlim - x) * 2 + dd;
	      if (v > 12 * (c + (dd < 0 ? -dd : dd)))
		{
		  if (v > best
		      && xoff < x && x <= xlim - SNAKE_LIMIT
		      && yoff < y && y <= ylim - SNAKE_LIMIT)
		    {
		      /* We have a good enough best diagonal;
			 now insist that it end with a significant snake.  */
		      int k;

		      for (k = 0; xv[x + k] == yv[y + k]; k++)
			if (k == SNAKE_LIMIT - 1)
			  {
			    best = v;
			    part->xmid = x;
			    part->ymid = y;
			    break;
			  }
		    }
		}
	    }
	  if (best > 0)
	    {
	      part->lo_minimal = false;
	      part->hi_minimal = true;
	      return;
	    }
	}

      /* Heuristic: if we've gone well beyond the call of duty,
	 give up and report halfway between our best results so far.  */
      if (c >= too_expensive)
	{
	  lin fxybest, fxbest;
	  lin bxybest, bxbest;

	  fxbest = bxbest = 0;  /* Pacify `gcc -Wall'.  */

	  /* Find forward diagonal that maximizes X + Y.  */
	  fxybest = -1;
	  for (d = fmax; d >= fmin; d -= 2)
	    {
	      lin x = MIN (fd[d], xlim);
	      lin y = x - d;
	      if (ylim < y)
		x = ylim + d, y = ylim;
	      if (fxybest < x + y)
		{
		  fxybest = x + y;
		  fxbest = x;
		}
	    }

	  /* Find backward diagonal that minimizes X + Y.  */
	  bxybest = LIN_MAX;
	  for (d = bmax; d >= bmin; d -= 2)
	    {
	      lin x = MAX (xoff, bd[d]);
	      lin y = x - d;
	      if (y < yoff)
		x = yoff + d, y = yoff;
	      if (x + y < bxybest)
		{
		  bxybest = x + y;
		  bxbest = x;
		}
	    }

	  /* Use the better of the two diagonals.  */
	  if ((xlim + ylim) - bxybest < fxybest - (xoff + yoff))
	    {
	      part->xmid = fxbest;
	      part->ymid = fxybest - fxbest;
	      part->lo_minimal = true;
	      part->hi_minimal = false;
	    }
	  else
	    {
	      part->xmid = bxbest;
	      part->ymid = bxybest - bxbest;
	      part->lo_minimal = false;
	      part->hi_minimal = true;
	    }
	  return;
	}
    }
}